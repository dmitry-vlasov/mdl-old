/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_owl_func_parser_Source.cpp                           */
/* Description:     functional OWL2 source parser                            */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "del/owl/func/lexer/del_owl_func_lexer.hpp"
#include "del/owl/func/source/del_owl_func_source.hpp"
#include "del/owl/func/parser/del_owl_func_parser.hpp"

namespace del {
namespace owl {
namespace func {
namespace parser {

	/****************************
	 *		Public members
	 ****************************/

	Source :: Source () :
	lexer_ (NULL),
	name_ (INITIAL_NAME_CAPACITY),
	namespaceParser_ (new parser :: Namespace()),
	prefixParser_ (new parser :: Prefix()),
	ontologyParser_ (new parser :: Ontology()),
	unrecognizedParser_ (new parser :: Unrecognized()) {
	}
	Source :: ~ Source()
	{
		deleteAggregateObject (lexer_);
		deleteAggregateObject (namespaceParser_);
		deleteAggregateObject (prefixParser_);
		deleteAggregateObject (ontologyParser_);
		deleteAggregateObject (unrecognizedParser_);
	}

using manipulator :: endLine;

	const source :: Source*
	Source :: parse (const del :: Path& path)
	{
		open (path);
		source :: Source* const source =
			(Config :: getTarget().isUndefined()) ?
			new source :: Source (path) :
			new source :: Source (path, Config :: getTarget());

		bool inPrefix = true;
		while (inPrefix) {
			lexer_->scan
			<
				Token :: NAMESPACE,
				Token :: PREFIX,
				Token :: STRING,
				Token :: ONTOLOGY
			>();
			switch (lexer_->getTokenType()) {
			case Token :: NAMESPACE : {
				const source :: Namespace*
					namespacee = namespaceParser_->parse (lexer_);
				source->addNamespace (namespacee);
				break;
			}
			case Token :: PREFIX : {
				const source :: Prefix*
					prefix = prefixParser_->parse (lexer_);
				source->addPrefix (prefix);
				break;
			}
			case Token :: STRING : {
				name_.copy (lexer_->getToken());
				const source :: Unrecognized*
					unrecognized = unrecognizedParser_->parse (name_, lexer_);
				source->addUnrecognized (unrecognized);
				break;
			}
			case Token :: ONTOLOGY :
				inPrefix = false;
				break;
			}
		}
		const source :: Ontology*
			ontology = ontologyParser_->parse (lexer_);
		source->setOntology (ontology);
		lexer_->scan<Token :: EOF_>();
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
		volume += name_.getVolume();
		volume += getAggregateVolume (lexer_);
		volume += getAggregateVolume (namespaceParser_);
		volume += getAggregateVolume (prefixParser_);
		volume += getAggregateVolume (ontologyParser_);
		volume += getAggregateVolume (unrecognizedParser_);
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


