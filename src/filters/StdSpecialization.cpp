#include <clang/AST/DeclTemplate.h>
#include <clang/AST/RecursiveASTVisitor.h>

#include "Census.h"
#include "census_lib.h"

using namespace clang;

namespace census {
namespace {

bool inStd(const Decl *D) {
  const NamespaceDecl *Top = nullptr;
  for (const DeclContext *DC = D->getDeclContext(); DC; DC = DC->getParent())
    if (const auto *NS = dyn_cast<NamespaceDecl>(DC))
      Top = NS;
  return Top && Top->getName() == "std";
}

std::string name(const NamedDecl *D) {
  std::string Name;
  llvm::raw_string_ostream OS(Name);
  PrintingPolicy Policy(D->getASTContext().getLangOpts());
  Policy.SuppressInlineNamespace =
      static_cast<unsigned>(PrintingPolicy::SuppressInlineNamespaceMode::All);
  D->getNameForDiagnostic(OS, Policy, true);
  return Name;
}

class Visitor : public RecursiveASTVisitor<Visitor> {
public:
  explicit Visitor(ASTContext &Ctx) : Ctx(Ctx) {}

  bool
  VisitClassTemplateSpecializationDecl(ClassTemplateSpecializationDecl *D) {
    if (D->getSpecializationKind() == TSK_ExplicitSpecialization &&
        inStd(D->getSpecializedTemplate()) && !IsInSystemHeader(D))
      report(Ctx, "std-specialization", D->getLocation(), "class " + name(D));
    return true;
  }

  bool VisitVarTemplateSpecializationDecl(VarTemplateSpecializationDecl *D) {
    if (D->getSpecializationKind() == TSK_ExplicitSpecialization &&
        inStd(D->getSpecializedTemplate()) && !IsInSystemHeader(D))
      report(Ctx, "std-specialization", D->getLocation(),
             "variable " + name(D));
    return true;
  }

  bool VisitFunctionDecl(FunctionDecl *D) {
    if (D->getTemplateSpecializationKind() != TSK_ExplicitSpecialization ||
        IsInSystemHeader(D))
      return true;
    const Decl *Primary = D->getPrimaryTemplate();
    if (!Primary)
      Primary = D->getInstantiatedFromMemberFunction();
    if (!Primary)
      Primary = D;
    if (inStd(Primary) || inStd(D))
      report(Ctx, "std-specialization", D->getLocation(),
             (isa<CXXMethodDecl>(D) ? "member " : "function ") + name(D));
    return true;
  }

private:
  ASTContext &Ctx;
};

} // namespace

void Filters::HasStdSpecialization(ASTContext &Ctx) {
  Visitor(Ctx).TraverseDecl(Ctx.getTranslationUnitDecl());
}

} // namespace census
