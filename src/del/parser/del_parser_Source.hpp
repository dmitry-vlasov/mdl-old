/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_parser_Source.hpp                                    */
/* Description:     source parser                                            */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef DEL_PARSER_SOURCE_HPP_
#define DEL_PARSER_SOURCE_HPP_

#include "del/interface/del_interface.hpp"
#include "del/lexer/del_lexer.hpp"
#include "del/parser/del_parser.dpp"

namespace del {
namespace parser {

class Source :
	public Object,
	public Scalar<Source> {
public :
	Source();
	virtual ~ Source();

	const del :: Source* parse (const del :: Path&);

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	void open (const Path&);
	void close (const Path&);

	Lexer* lexer_;

	// internal part
	parser :: Assertion* assertionParser_;
	parser :: Theory*    theoryParser_;
	parser :: Question*  questionParser_;
	parser :: Answer*    answerParser_;
	parser :: Signature* signatureParser_;
	parser :: Decompose*     decomposeParser_;
	parser :: Decomposition* decompositionParser_;
	parser :: Minimize*      minimizeParser_;
	parser :: Minimization*  minimizationParser_;
 };

}
}

#endif /*DEL_PARSER_SOURCE_HPP_*/
