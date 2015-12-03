/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression.cpp                                       */
/* Description:     expression module                                        */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_EXPRESSION_CPP_
#define MDL_EXPRESSION_CPP_

#include "mdl/expression/mdl_expression.ipp"
#include "mdl/expression/simify/mdl_expression_simify.cpp"
#include "mdl/expression/unify/mdl_expression_unify.cpp"
#include "mdl/expression/mdl_expression_Symbol.cpp"

namespace mdl {

void dump (const array :: Substitution* x) { x->dump(); }
void dump (const array :: Substitution& x) { x.dump();  }
void dump (const array :: Expression* x) { x->dump(); }
void dump (const array :: Expression& x) { x.dump();  }
void dump (const array :: Term* x) { x->dump(); }
void dump (const array :: Term& x) { x.dump();  }

void dump (const stack :: Substitution* x) { x->dump(); }
void dump (const stack :: Substitution& x) { x.dump();  }
void dump (const stack :: Expression* x) { x->dump(); }
void dump (const stack :: Expression& x) { x.dump();  }
void dump (const stack :: Term* x) { x->dump(); }
void dump (const stack :: Term& x) { x.dump();  }

void dump (const list :: Substitution* x) { x->dump(); }
void dump (const list :: Substitution& x) { x.dump();  }
void dump (const list :: Expression* x) { x->dump(); }
void dump (const list :: Expression& x) { x.dump();  }
void dump (const list :: Term* x) { x->dump(); }
void dump (const list :: Term& x) { x.dump();  }

void dump (const expression :: Array<allocator :: Boxed>* x) { x->dump(); }
void dump (const expression :: Array<allocator :: Boxed>& x) { x.dump();  }
void dump (const expression :: Array<allocator :: Boxed> :: Substitution_* x) { x->dump(); }
void dump (const expression :: Array<allocator :: Boxed> :: Substitution_& x) { x.dump();  }
void dump (const expression :: Array<allocator :: Boxed> :: Term_* x) { x->dump(); }
void dump (const expression :: Array<allocator :: Boxed> :: Term_& x) { x.dump();  }

void dump (const expression :: List<allocator :: Boxed>* x) { x->dump(); }
void dump (const expression :: List<allocator :: Boxed>& x) { x.dump();  }
void dump (const expression :: List<allocator :: Boxed> :: Substitution_* x) { x->dump(); }
void dump (const expression :: List<allocator :: Boxed> :: Substitution_& x) { x.dump();  }
void dump (const expression :: List<allocator :: Boxed> :: Term_* x) { x->dump(); }
void dump (const expression :: List<allocator :: Boxed> :: Term_& x) { x.dump();  }

void dump (const unify :: sub :: tree :: HeapCell* x) { x->dump(); }
void dump (const unify :: sub :: tree :: HeapCell& x) { x.dump();  }
void dump (const unify :: sub :: tree :: HeapCell :: Substitution_* x) { x->dump(); }
void dump (const unify :: sub :: tree :: HeapCell :: Substitution_& x) { x.dump();  }
void dump (const unify :: sub :: tree :: HeapCell :: Term_* x) { x->dump(); }
void dump (const unify :: sub :: tree :: HeapCell :: Term_& x) { x.dump();  }

void dump (const unify :: sub :: tree :: BoxedCell* x) { x->dump(); }
void dump (const unify :: sub :: tree :: BoxedCell& x) { x.dump();  }
void dump (const unify :: sub :: tree :: BoxedCell :: Substitution_* x) { x->dump(); }
void dump (const unify :: sub :: tree :: BoxedCell :: Substitution_& x) { x.dump();  }
void dump (const unify :: sub :: tree :: BoxedCell :: Term_* x) { x->dump(); }
void dump (const unify :: sub :: tree :: BoxedCell :: Term_& x) { x.dump();  }

}

#endif /*MDL_EXPRESSION_CPP_*/
