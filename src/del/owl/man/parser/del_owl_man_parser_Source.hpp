/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_owl_man_parser_Source.hpp                            */
/* Description:     manchester OWL source parser                             */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef DEL_OWL_MAN_PARSER_SOURCE_HPP_
#define DEL_OWL_MAN_PARSER_SOURCE_HPP_

#include "del/owl/man/lexer/del_owl_man_lexer.hpp"
#include "del/owl/man/parser/del_owl_man_parser.dpp"
#include "del/owl/man/source/del_owl_man_source.dpp"

namespace del {
namespace owl {
namespace man {
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

	// internal part
	parser :: Namespace* namespaceParser_;
	parser :: Ontology* ontologyParser_;
	parser :: Annotations* annotationsParser_;
	parser :: ObjectProperty* objectPropertyParser_;
	parser :: Class* classParser_;
};

}
}
}
}

#endif /*DEL_OWL_MAN_PARSER_SOURCE_HPP_*/
