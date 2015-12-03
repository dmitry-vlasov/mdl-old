/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_parser_Source.cpp                                    */
/* Description:     source parser                                            */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_PARSER_SOURCE_CPP_
#define MDL_PARSER_SOURCE_CPP_

#include "mdl/lexer/mdl_lexer.hpp"
#include "mdl/form/mdl_form.hpp"
#include "mdl/parser/mdl_parser.hpp"

namespace mdl {
namespace parser {

	/****************************
	 *		Public members
	 ****************************/

	Source :: Source (const bool isTop) :
	isTop_ (isTop),
	lexer_ (NULL),
	importParser_ (new parser :: Import()),
	theoryParser_ (new parser :: Theory()),
	sourceParser_ (NULL),
	contentsParser_ (new parser :: Contents()),
	rootTheory_ (NULL)
	{
		if (isTop_) {
			if (parser_ != NULL) {
				parser_->commitSuicide();
			}
			parser_ = this;
		}
	}
	Source :: ~ Source()
	{
		if (isTop_) {
			parser_ = NULL;
		}
		deleteAggregateObject (importParser_);
		deleteAggregateObject (theoryParser_);
		deleteAggregateObject (sourceParser_);
		deleteAggregateObject (contentsParser_);
	}

	mdl :: Source*
	Source :: parse (const mdl :: Path* path)
	{
		Table :: names()->add (path->getName());
		if (isTop_) {
			Table :: files()->add (path->getString());
		}
		open (path);
		lexer_->scanComments();
		const mdl :: Comments* comments =
			lexer_->comments().isEmpty() ?
			NULL :
			new form :: Comments (lexer_->comments());
		lexer_->comments().clear();

		mdl :: Source* const source = new form :: Source (isTop_, lexer_, comments, path);

		if (rootTheory_ == NULL) {
			rootTheory_ = Math ::theories()->getRoot();
		}
		while (true) {
			lexer_->scan
			<
				Token :: IMPORT,
				Token :: THEORY,
				Token :: CONTENTS,
				Token :: EOF_
			>();
			switch (lexer_->getTokenType()) {
			case Token :: IMPORT : {
				mdl :: Import*
					import = importParser_->parse (lexer_);
				const String& importPath = import->getPath()->getString();
				source->addComponentLast (import);

				if (!Table :: files()->contains (importPath) &&
					!Config :: localParsing()) {
					Table :: files()->add (importPath);
					if (sourceParser_ == NULL) {
						sourceParser_ = new parser :: Source (false);
					}
					mdl :: Source*
						importedSource = sourceParser_->parse (import->getPath());
					source->addComponentLast (importedSource);
				}
				break;
			}
			case Token :: THEORY : {
				mdl :: Theory*
					theory = theoryParser_->parse (lexer_, rootTheory_);
				source->addComponentLast (theory);
				break;
			}
			case Token :: CONTENTS : {
				mdl :: Contents*
					contents = contentsParser_->parse (lexer_, rootTheory_);
				source->addComponentLast (contents);
				break;
			}
			case Token :: EOF_ : {
				lexer_->getLocation();
				goto end;
			}
			default :
				return NULL;
			}
		}
		end :
		close (path);
		return source;
	}
	Source*
	Source :: get() {
		return parser_;
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
		volume += getAggregateVolume (importParser_);
		volume += getAggregateVolume (theoryParser_);
		volume += getAggregateVolume (sourceParser_);
		volume += getAggregateVolume (contentsParser_);
		if (isTop_) {
			volume +=getSizeOf();
		}
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
	Source :: open (const Path* path)
	{
		const String& file = path->getString();
		lexer_ = new Lexer (file, isTop_);
		lexer_->open();
	}
	void
	Source :: close (const Path* path)
	{
		if (lexer_ == NULL) {
			Error* error = new Error (Error :: INPUT);
			error->message() << "attempt to close non opened " << *path << endLine;
			throw error;
		}
		if (lexer_->getTokenType() != Token :: EOF_) {
			Error* error = new Error (Error :: INPUT);
			error->message() << "unexpected token: "<< lexer_->getToken() << endLine;
			error->message() << "EOF expected in file " << *path << endLine;
			throw error;
		}
		lexer_->close();
	}

	/************************************
	 *		Private static attributes
	 ************************************/

	Source* Source :: parser_ = NULL;
}
}

#endif /*MDL_PARSER_SOURCE_CPP_*/
