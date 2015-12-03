/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_owl_func_parser_Source.hpp                           */
/* Description:     functional OWL2 source parser                            */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef DEL_OWL_FUNC_PARSER_SOURCE_HPP_
#define DEL_OWL_FUNC_PARSER_SOURCE_HPP_

#include "del/owl/func/lexer/del_owl_func_lexer.hpp"
#include "del/owl/func/parser/del_owl_func_parser.dpp"
#include "del/owl/func/source/del_owl_func_source.dpp"

namespace del {
namespace owl {
namespace func {
namespace parser {

class Source :
	public Object,
	public Scalar<Source> {
public :
	Source();
	virtual ~ Source();

	const source :: Source* parse (const del :: Path&);

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	void open (const Path&);
	void close (const Path&);

	Lexer* lexer_;
	// external part
	String name_;

	// internal part
	parser :: Namespace* namespaceParser_;
	parser :: Prefix* prefixParser_;
	parser :: Ontology*  ontologyParser_;
	parser :: Unrecognized* unrecognizedParser_;

	enum {
		INITIAL_NAME_CAPACITY = 32
	};
};

}
}
}
}

#endif /*DEL_OWL_FUNC_PARSER_SOURCE_HPP_*/
