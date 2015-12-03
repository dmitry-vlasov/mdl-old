/*****************************************************************************/
/* Project name:    smm - verifier for the Simplified MetaMath language      */
/* File name:       smm_parser_Vector.hpp                                    */
/* Description:     literal vector parser                                    */
/* Copyright:       (c) 2006-2010 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef SMM_PARSER_VECTOR_HPP_
#define SMM_PARSER_VECTOR_HPP_

#include "smm/interface/smm_interface.hpp"
#include "smm/parser/smm_parser.dpp"
#include "smm/lexer/smm_lexer.hpp"

namespace smm {
namespace parser {

template
<
	Token :: Type B,                // begin token
	bool f = true,                  // scan begin token
	Token :: Type E = Token :: END  // end token
>
class Vector :
	public object :: Object,
	public Scalar<Vector<B, f, E> > {
public :
	Vector ();
	virtual ~ Vector();

	const vector :: Literal& parse (Lexer* const);

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	vector :: Literal literalVector_;
	enum {
		INITIAL_LITERAL_VECTOR_CAPACITY = 256,
	};
};

}
}

#include "smm/parser/smm_parser_Vector.ipp"

#endif /*SMM_PARSER_VECTOR_HPP_*/
