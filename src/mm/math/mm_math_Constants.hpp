/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_math_Constants.hpp                                    */
/* Description:     global metamath constants container                      */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MM_MATH_CONSTANTS_HPP_
#define MM_MATH_CONSTANTS_HPP_

#include "interface/mm_interface.hpp"
#include "math/mm_math.dpp"

namespace mm {
namespace math {

class Constants :
	public object :: Object,
	public Scalar<Constants> {
public :
	Constants();
	virtual ~ Constants();

	void add (const mm :: source :: Constants* const);
	bool contain (const value :: Literal);

	value :: Literal turnstile() const;
	value :: Literal openBracket() const;
	value :: Literal closeBracket() const;
	value :: Literal openBrace() const;
	value :: Literal closeBrace() const;
	value :: Literal equality() const;
	value :: Literal equivalence() const;

	value :: Literal wff() const;
	value :: Literal set() const;
	value :: Literal _class() const;

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	vector :: Literal constantSet_;
	index :: Literal constantCount_;

	// base alphabet symbols
	value :: Literal turnstile_;
	value :: Literal openBracket_;
	value :: Literal closeBracket_;
	value :: Literal openBrace_;
	value :: Literal closeBrace_;
	value :: Literal equality_;
	value :: Literal equivalence_;

	// base type symbols
	value :: Literal wff_;
	value :: Literal set_;
	value :: Literal class_;

	// procedure for initialization of basic symbols.
	/**
	 * integer representations of symbols:
	 * \li \c |- - turnstile
	 * \li \c ( - open bracket
	 * \li \c ) - close bracket
	 * \li \c { - open brace
	 * \li \c } - close brace
	 * \li \c = - equality symbol
	 * \li \c <-> - symbol of equality
	 *
	 * \li \c wff - type wff
	 * \li \c set - type set
	 * \li \c class - type class
	 * */
	void initConstants ();

	enum {
		INITIAL_CONSTANTS_CAPACITY = 4096
	};
};

}
}

#include "math/mm_math_Constants.ipp"

#endif /*MM_MATH_CONSTANTS_HPP_*/
