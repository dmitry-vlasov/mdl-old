/*****************************************************************************/
/* Project name:    smm - verifier for the Simplified MetaMath language      */
/* File name:       smm_parser_Line.hpp                                      */
/* Description:     assertion line parser                                    */
/* Copyright:       (c) 2006-2010 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef SMM_PARSER_LINE_HPP_
#define SMM_PARSER_LINE_HPP_

#include "smm/interface/smm_interface.hpp"
#include "smm/parser/smm_parser.dpp"
#include "smm/lexer/smm_lexer.hpp"

namespace smm {
namespace parser {

template
<
	Token :: Type B,               // begin token
	bool f = true,                 // scan begin token
	bool i = true,                 // true: scan indexes / false: scan labels
	Token :: Type E = Token :: END // end token
>
class Line :
	public object :: Object,
	public Scalar<Line<B, f, i, E> > {
public :
	Line ();
	virtual ~ Line();

	const Expression* parse
	(
		Lexer* const,
		const value :: Index = value :: undefined :: INDEX
	);
	value :: Index getIndex() const;

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	Location location_;
	value :: Index index_;
	typedef
		parser :: Vector<B, f, E>
		VectorParser_;
	VectorParser_* vectorParser_;
};

}
}

#include "smm/parser/smm_parser_Line.ipp"

#endif /*SMM_PARSER_LINE_HPP_*/
