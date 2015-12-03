/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_unify_sub_prod_Matirx.ipp                 */
/* Description:     most general matrix unifier module                       */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_EXPRESSION_UNIFY_SUB_PROD_MATRIX_IPP_
#define MDL_EXPRESSION_UNIFY_SUB_PROD_MATRIX_IPP_

namespace mdl {
namespace expression {
namespace unify {
namespace sub {
namespace prod {

	/****************************
	 *		Public members
	 ****************************/

	template<class T, int P, int K, class A>
	inline
	Matrix<T, P, K, A> :: Matrix (const Substivector_& substivector) :
	data_ (substivector),
	dimensionX_ (substivector.getSize()),
	dimensionY_ (0),
	variables_ (),
	exprematrix_ (),
	delta_ (NULL),
	epsilon_ (NULL),
	vectorUnifier_ (this, dimensionX_, delta_, epsilon_)
	{
		calculateVariables();
		fillMatrix();
	}

	template<class T, int P, int K, class A>
	inline bool
	Matrix<T, P, K, A> :: unify()
	{
		for (index :: Arity i = 0; i < dimensionY_; ++ i) {
			const InnerExprevector_* const
				exprevector = exprematrix_.getValue (i);
			if (!vectorUnifier_.unify (exprevector)) {
				return false;
			} else {
				executeDelta();
			}
		}
		return true;
		#ifdef DEBUG
		if ((dimensionX_ > 1) && (dimensionY_ > 1)) {
			try {
				verifyIntegrity();
				//std :: cout << *this << std :: endl << std :: endl << std :: endl;
			} catch (Error* error) {
				std :: cout << *this << std :: endl << std :: endl << std :: endl;
				std :: cout << error->message() << std :: endl;
				throw error;
			}
		}
		#endif /*DEBUG*/
	}

using manipulator :: endLine;
using manipulator :: space;
using manipulator :: tab;

	template<class T, int P, int K, class A>
	void
	Matrix<T, P, K, A> :: show (String& string) const
	{
		Mode mode (string);
		Mode m (mode);
		m << Mode :: SHOW_REPLACEABILITY;
		string << m;
		string << "--------------------------" << endLine;
		string << endLine;
		string << "data_ = " << endLine;
		for (index :: Arity i = 0; i < dimensionX_; ++ i) {
			const Substitution_* substitution = data_.getValue (i);
			if (substitution == NULL) {
				string << tab << i << " = NULL" << endLine;
			} else {
				string << tab << i << " = " << *substitution << endLine;
			}
		}
		string << "--------------------------" << endLine;

		string << "dimensionX_ = " << dimensionX_ << endLine;
		string << "dimensionY_ = " << dimensionY_ << endLine;
		string << "variables_ = " << dimensionY_ << endLine;
		for (index :: Arity i = 0; i < variables_.getSize(); ++ i) {
			string << variables_.getValue (i) << space;
		}
		string << endLine;
		string << endLine;
		string << "exprematrix_ = " << endLine;
		string << "rows    - vectors of expressions - to unify" << endLine;
		string << "columns - variable of the substitution" << endLine;
		string << "--------------------------" << endLine;
		for (index :: Arity i = 0; i < dimensionY_; ++ i) {
			const InnerExprevector_* const
				exprevector = exprematrix_.getValue (i);
			string << i << " exprevector: " << endLine;
			for (index :: Arity j = 0; j < dimensionX_; ++ j) {
				const InnerExpression_* const
					expression = exprevector->getValue (j);
				if (expression == NULL) {
					string << "NULL" << tab;
				} else {
					string << *expression << tab;
				}
			}
			string << endLine;
		}
		string << "--------------------------" << endLine;
		string << endLine;
		string << "epsilon_ = ";
		if (epsilon_ == NULL) {
			string << "NULL" << endLine;
		} else {
			string << *epsilon_ << endLine;
		}
		string << "delta_ = ";
		if (delta_ == NULL) {
			string << "NULL" << endLine;
		} else {
			string << *delta_ << endLine;
		}
		string << "--------------------------" << endLine;
		string << mode;
	}

	/****************************
	 *		Private members
	 ****************************/

	template<class T, int P, int K, class A>
	void
	Matrix<T, P, K, A> :: calculateVariables()
	{
		for (index :: Arity i = 0 ; i < dimensionX_; ++ i) {
			const Substitution_*
				substitution = data_.getValue (i);
			#ifdef DEBUG
			substitution->verifyIntegrity();
			#endif
			while (substitution != NULL) {
				const Symbol&
					variable = substitution->getVariable();
				if (!variables_.contains (variable)) {
					variables_.add (variable);
				}
				substitution = substitution->getNext();
			}
		}
		const_cast<index :: Arity&>(dimensionY_) = variables_.getSize();
	}
	template<class T, int P, int K, class A>
	void
	Matrix<T, P, K, A> :: fillMatrix()
	{
		for (index :: Arity i = 0; i < dimensionY_; ++ i) {
			InnerExprevector_* const
				exprevector = new InnerExprevector_ (dimensionX_);
			const Symbol&
				columnVariable = variables_.getReference (i);

			for (index :: Arity j = 0; j < dimensionX_; ++ j) {
				const Substitution_*
					substitution = data_.getValue (j);
				while (substitution != NULL) {
					#ifdef DEBUG
					substitution->verifyIntegrity();
					#endif
					const Symbol&
						rowVariable = substitution->getVariable();
					if (rowVariable == columnVariable) {
						const Term_* const
							term = substitution->getTerm();
						InnerExpression_* const
							innerExpression = InnerExpression_ :: template
								createList<Term_> (term);
						#ifdef DEBUG
						term->verifyIntegrity();
						innerExpression->verifyIntegrity();
						#endif
						exprevector->add (innerExpression);
						break;
					}
					substitution = substitution->getNext();
				}
				if (substitution == NULL) {
					exprevector->add (NULL);
				}
			}
			exprematrix_.push() = exprevector;
		}
	}
	template<class T, int P, int K, class A>
	inline void
	Matrix<T, P, K, A> :: executeDelta()
	{
		for (index :: Arity j = 0; j < dimensionY_; ++ j) {
			const InnerExprevector_* const
				exprevector = exprematrix_.getValue (j);
			for (index :: Arity k = 0; k < dimensionX_; ++ k) {
				InnerExpression_* const
					expression = exprevector->getValue (k);

				#ifdef DEBUG
				if (epsilon_ != NULL) {
					epsilon_->verifyIntegrity();
				}
				#endif
				if (expression != NULL) {
					#ifdef DEBUG
					expression->verifyIntegrity();
					#endif
					expression->execute (epsilon_);
					#ifdef DEBUG
					expression->verifyIntegrity();
					#endif
				}
			}
		}
	}

	template<class T, int P, int K, class A>
	void
	Matrix<T, P, K, A> :: verifyIntegrity() const
	{
		for (index :: Arity i = 0; i < dimensionY_; ++ i) {
			const InnerExprevector_*
				exprevector = exprematrix_.getValue (i);
			verifyColumn (exprevector);
		}
	}
	template<class T, int P, int K, class A>
	void
	Matrix<T, P, K, A> :: verifyColumn (const InnerExprevector_* exprevector) const
	{
		InnerExpression_* expressions [dimensionX_];
		for (index :: Arity i = 0; i < dimensionX_; ++ i) {
			const InnerExpression_*
				expression = exprevector->getValue (i);
			if (expression == NULL) {
				expressions [i] = NULL;
			} else {
				#ifdef DEBUG
				expression->verifyIntegrity();
				#endif
				expressions [i] = new InnerExpression_ (expression);
				expressions [i]->execute (delta_);
			}
		}
		for (index :: Arity i = 0; i < dimensionX_ - 1; ++ i) {
			const InnerExpression_*
				expression_1 = expressions [i];
			if (expression_1 == NULL) {
				continue;
			}
			for (index :: Arity j = i + 1; j < dimensionX_; ++ j) {
				const InnerExpression_*
					expression_2 = expressions [j];
				if (expression_2 == NULL) {
					continue;
				}
				if (*expression_1 != *expression_2) {
					Error* error = new Error (Error :: SEMANTIC);
					Mode m;
					m << Mode :: SHOW_REPLACEABILITY;
					error->message() << m;
					error->message() << "incorrect mgu unification:" << endLine;
					error->message() << "expression 1 = " << *expression_1 << endLine;
					error->message() << "expression 2 = " << *expression_2 << endLine;
					throw error;
				}
			}
		}
	}

	template<class T, int P, int K, class A>
	void
	Matrix<T, P, K, A> :: verifyExpressions (const bool show) const
	{
		for (value :: Integer i = 0; i < exprematrix_.getSize(); ++ i) {
			const InnerExprevector_* const
				exprevector = exprematrix_.getValue (i);
			for (value :: Integer j = 0; j < exprevector->getSize(); ++ j) {
				if (show) {
					std :: cout << "exp [" << i << ", " << j << "] = ";
					if (exprevector->getValue (j) == NULL) {
						std :: cout << "NULL";
					} else {
						std :: cout << *exprevector->getValue (j) << " ";
						std :: cout << "term - " << (void*)exprevector->getValue (j)->getTerm() << " ";
						exprevector->getValue (j)->verifyIntegrity();
					}
					std :: cout << std :: endl;
				}
			}
		}
		if (show) {
			std :: cout << std :: endl << std :: endl;
		}
	}

	/********************************
	 *		Overloaded operators
	 ********************************/

	template<class T, int P, int K, class A>
	inline String&
	operator << (String& string, const Matrix<T, P, K, A>& matrix)
	{
		matrix.show (string);
		return string;
	}
	template<class T, int P, int K, class A>
	inline std :: ostream&
	operator << (std :: ostream& os, const Matrix<T, P, K, A>& matrix)
	{
		String str (1024);
		return os << (str << matrix);
	}
}
}
}
}
}

#endif /*MDL_EXPRESSION_UNIFY_SUB_PROD_MATRIX_IPP_*/
