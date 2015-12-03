/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_owl_man_parser_Source.cpp                            */
/* Description:     OWL source parser                                        */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef DEL_OWL_MAN_PARSER_SOURCE_CPP_
#define DEL_OWL_MAN_PARSER_SOURCE_CPP_

#include "del/owl/man/lexer/del_owl_man_lexer.hpp"
#include "del/owl/man/source/del_owl_man_source.hpp"
#include "del/owl/man/parser/del_owl_man_parser.hpp"

namespace del {
namespace owl {
namespace man {
namespace parser {

	/****************************
	 *		Public members
	 ****************************/

	Source :: Source () :
	lexer_ (NULL),
	namespaceParser_ (new parser :: Namespace()),
	ontologyParser_ (new parser :: Ontology()),
	annotationsParser_ (new parser :: Annotations()),
	objectPropertyParser_ (new parser :: ObjectProperty()),
	classParser_ (new parser :: Class()) {
	}
	Source :: ~ Source()
	{
		deleteAggregateObject (lexer_);
		deleteAggregateObject (namespaceParser_);
		deleteAggregateObject (ontologyParser_);
		deleteAggregateObject (annotationsParser_);
		deleteAggregateObject (objectPropertyParser_);
		deleteAggregateObject (classParser_);
	}

using manipulator :: endLine;

	const source :: Source*
	Source :: parse (const del :: Path& path)
	{
		open (path);
		lexer_->scanComments();
		lexer_->comments().clear();
		source :: Source* const source =
			(Config :: getTarget().isUndefined()) ?
			new source :: Source (path) :
			new source :: Source (path, Config :: getTarget());

		while (true) {
			switch (lexer_->scan()) {
			case Token :: NAMESPACE : {
				const source :: Namespace*
					nspace = namespaceParser_->parse (lexer_);
				source->addNamespace (nspace);
				break;
			}
			case Token :: ONTOLOGY : {
				const source :: Ontology*
					ontology = ontologyParser_->parse (lexer_);
				source->addOntology (ontology);
				break;
			}
			case Token :: ANNOTATIONS : {
				const source :: Annotations*
					annotations = annotationsParser_->parse (lexer_);
				source->addAnnotations (annotations);
				break;
			}
			case Token :: OBJECT_PROPERTY : {
				const source :: ObjectProperty*
					objectProperty = objectPropertyParser_->parse (lexer_);
				source->addObjectProperty (objectProperty);
				break;
			}
			case Token :: CLASS : {
				const source :: Class*
					clas = classParser_->parse (lexer_);
				source->addClass (clas);
				break;
			}
			case Token :: EOF_ : {
				lexer_->getLocation();
				goto end;
			}
			default :
				Error* error = new Error (lexer_->getLocation(), Error :: PARSER);
				error->message() << "syntax error." << endLine;
				error->message() << "token: \"" << lexer_->getToken() << "\" was scanned" << endLine;
				error->message() << "wile one of Namespace, Ontology, ObjectProperty, Annotations, Class was expected" << endLine;
				throw error;
			}
		}
		end :
		lexer_->comments().clear();
		close (path);
		return source;
	}

	// object :: Object implementation
	void
	Source :: commitSuicide() {
		delete this;
	}
	Size_t
	Source :: getVolume() const
	{
		Size_t volume = 0;
		volume += getAggregateVolume (lexer_);
		volume += getAggregateVolume (namespaceParser_);
		volume += getAggregateVolume (ontologyParser_);
		volume += getAggregateVolume (annotationsParser_);
		volume += getAggregateVolume (objectPropertyParser_);
		volume += getAggregateVolume (classParser_);
		return volume;
	}
	Size_t
	Source :: getSizeOf() const {
		return sizeof (Source);
	}
	void
	Source :: show (String&) const {
	}

	/****************************
	 *		Private members
	 ****************************/

using manipulator :: endLine;

	void
	Source :: open (const Path& path)
	{
		const String& file = path.getString();
		lexer_ = new Lexer (file);
		lexer_->open();
	}
	void
	Source :: close (const Path& path)
	{
		if (lexer_ == NULL) {
			Error* error = new Error (Error :: INPUT);
			error->message() << "attempt to close non opened " << path << endLine;
			throw error;
		}
		if (lexer_->getTokenType() != Token :: EOF_) {
			Error* error = new Error (Error :: INPUT);
			error->message() << "unexpected token: "<< lexer_->getToken() << endLine;
			error->message() << "EOF expected in file " << path << endLine;
			throw error;
		}
		lexer_->close();
	}
}
}
}
}

#endif /*DEL_OWL_MAN_PARSER_SOURCE_CPP_*/
