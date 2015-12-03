/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_expression_unify_sub_Multyindex.ipp                  */
/* Description:     vector of evidence indexes                               */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_EXPRESSION_UNIFY_SUB_MULTYINDEX_IPP_
#define MDL_EXPRESSION_UNIFY_SUB_MULTYINDEX_IPP_

namespace mdl {
namespace expression {
namespace unify {
namespace sub {

	/****************************
	 *		Public members
	 ****************************/

	template<class C, class T>
	inline
	Multyindex<C, T> :: Multyindex
	(
		const index :: Arity dimension,
		const Matrix_& matrix
	) :
	dimension_ (dimension),
	matrix_ (matrix),
	indexVector_ (dimension)
	{
		for (index :: Arity d = 0; d < dimension_; ++ d) {
			indexVector_.push() = 0;
		}
	}

	template<class C, class T>
	inline index :: Arity
	Multyindex<C, T> :: getDimension() const {
		return dimension_;
	}
	template<class C, class T>
	inline bool
	Multyindex<C, T> :: operator ++() {
		return increment ();
	}
	template<class C, class T>
	typename Multyindex<C, T> :: Evidence_*
	Multyindex<C, T> :: getValue (const index :: Arity d) const
	{
		const Container_* container = matrix_.getValue (d);
		const value :: Integer index = indexVector_.getValue (d);
		return const_cast<Evidence_*>(container->getValue (index));
	}

	template<class C, class T>
	inline value :: Integer
	Multyindex<C, T> :: getSearchVolume() const
	{
		value :: Integer wholeVolume = 1;
		for (index :: Arity d = 0; d < dimension_; ++ d) {
			const Container_*
				container = matrix_.getValue (d);
			wholeVolume *= container->getSize();
		}
		return wholeVolume;
	}

using manipulator :: endLine;
using manipulator :: tab;
using manipulator :: space;

	template<class C, class T>
	template<class S>
	void
	Multyindex<C, T> :: show (S& string) const
	{
		string << "multyindex:" << endLine;
		string << "-----------" << endLine;
		string << tab << "dimension: " << dimension_ << endLine;
		string << tab << "components:" << endLine;
		string << tab << "----------" << endLine;
		for (index :: Arity d = 0; d < dimension_; ++ d) {
			const Container_* const
				container = matrix_.getValue (d);
			string << tab << tab << d << " index: " << indexVector_.getValue (d) << endLine;
			string << tab << tab << d << " size: " << container->getSize() << endLine;
			string << tab << tab << d << " boundary: " << container->getBoundary() << endLine;
			string << endLine;
		}
		string << tab << "search volume: " << getSearchVolume() << endLine;
		string << endLine;
	}
	template<class C, class T>
	void
	Multyindex<C, T> :: dump() const
	{
		enum {
			INITIAL_STRING_CAPACITY = 64
		};
		String string (INITIAL_STRING_CAPACITY);
		show (string);
		std :: cout << string;
	}

	/****************************
	 *		Protected members
	 ****************************/

	template<class C, class T>
	bool
	Multyindex<C, T> :: increment (const index :: Arity d)
	{
		if (d == dimension_) {
			return true;
		}
		const value :: Integer
			index = indexVector_.getValue (d);
		const value :: Integer
			size = matrix_.getValue (d)->getSize();

		if (index < size - 1) {
			++ indexVector_.getReference (d);
			return false;
		} else {
			indexVector_.getReference (d) = 0;
			return increment (d + 1);
		}
	}

	/********************************
	 *		Overloaded operators
	 ********************************/

	template<class S, class C, class T>
	inline S&
	operator << (S& string, const Multyindex<C, T>& multyindex)
	{
		multyindex.show (string);
		return string;
	}
	template<class C, class T>
	inline std :: ostream&
	operator << (std :: ostream& os, const Multyindex<C, T>& multyindex)
	{
		static String string (1024);
		return os << (string << multyindex);
	}
}
}
}
}

#endif /*MDL_EXPRESSION_UNIFY_SUB_MULTYINDEX_IPP_*/
