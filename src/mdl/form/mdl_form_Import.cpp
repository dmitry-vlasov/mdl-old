/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_form_Import.cpp                                      */
/* Description:     import class                                             */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "mdl/lexer/mdl_lexer.hpp"
#include "mdl/form/mdl_form_Identificator.hpp"
#include "mdl/form/mdl_form_Import.hpp"

#include "smm/auxiliary/smm_auxiliary_Config.hpp"
#include "smm/lexer/smm_lexer_Token.hpp"

namespace mdl {
namespace form {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Import :: Import
	(
		const Location& location,
		mdl :: Identificator* pathComponents
	) :
	location_ (location),
	pathComponents_ (pathComponents),
	sourcePath_ (),
	targetPath_ ()
	{
		mdl :: Identificator* pathComponent = pathComponents_;
		while (pathComponent != NULL) {
			const value :: Name
				component = pathComponent->getName();
			const String&
				string = Table :: names()->get (component);
			if (pathComponent->getNext() == NULL) {
				sourcePath_.name() = string;
				targetPath_.name() = string;
			} else {
				sourcePath_.pushDirectory() = string;
				targetPath_.pushDirectory() = string;
			}
			pathComponent = pathComponent->getNext();
		}
		sourcePath_.extension() = Config :: russellExtension();
		if (Config :: translate()) {
			targetPath_.extension() = smm :: Config :: smmExtension();
		} else {
			targetPath_.extension() = mdl :: Config :: russellExtension();
		}
	}
	Import :: ~ Import() {
		deleteAggregateObject (pathComponents_);
	}

	// mdl :: Import implementation
	Path*
	Import :: getPath() {
		return &sourcePath_;
	}
	const Path*
	Import :: getPath() const {
		return &sourcePath_;
	}

using manipulator :: endLine;
using manipulator :: space;
using manipulator :: tab;

	// object :: Verifiable implementation
	bool
	Import :: isVerified() const {
		return true;
	}
	void
	Import :: check() {
	}
	void
	Import :: compress() {
	}
	void
	Import :: reprove() {
	}
	void
	Import :: prove() {
	}
	void
	Import :: mine (String& string) const
	{
		if (!Config :: getMiningOptions().getValue (Config :: MINE_IMPORTS)) {
			return;
		}
		string << tab << "<import ";
		string << "name=\"";
		pathComponents_->replicate (string);
		string << "\" ";
		string << "from=\"" << sourcePath_ << "\" ";
		location_.showAttributes (string);
		string << "/>" << endLine;
	}

	// object :: Buildable implementation
	void
	Import :: build() {
	}

	// object :: Writable implementation
	void
	Import :: translate (String& string) const
	{
		string << location_.getIndent();
		string << :: smm :: Token :: inclusionBegin_ << space;
		string << targetPath_.getString() << space;
		string << :: smm :: Token :: inclusionEnd_ << endLine;
	}
	void
	Import :: replicate (String& string) const
	{
		string << location_.getIndent() << Token :: import_ << space;
		string << *pathComponents_ << Token :: semicolon_ << endLine;
	}
	bool
	Import :: lookup() const
	{
		if (location_.isNearestTo (Config :: getPosition())) {
			if (Config :: lookupLocation()) {
				std :: cout << "file: " << sourcePath_ << std :: endl;
			}
			return true;
		} else {
			return false;
		}
	}
	object :: Writable*
	Import :: find()
	{
		if (location_.isNearestTo (Config :: getPosition())) {
			return this;
		} else {
			return NULL;
		}
	}
	const object :: Writable*
	Import :: find() const
	{
		if (location_.isNearestTo (Config :: getPosition())) {
			return this;
		} else {
			return NULL;
		}
	}

	// object :: Object implementation
	void
	Import :: commitSuicide() {
		delete this;
	}
	Size_t
	Import :: getVolume() const
	{
		Size_t volume = 0;
		volume += getAggregateVolume (pathComponents_);
		volume += sourcePath_.getVolume();
		volume += targetPath_.getVolume();
		return volume;
	}
	Size_t
	Import :: getSizeOf() const {
		return sizeof (Import);
	}

	/****************************
	 *		Private members
	 ****************************/
}
}


