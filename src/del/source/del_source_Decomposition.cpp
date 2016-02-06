/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_source_Decomposition.cpp                             */
/* Description:     answer                                                   */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "del/lexer/del_lexer.hpp"
#include "del/source/del_source_Decomposition.hpp"

namespace del {
namespace source {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Decomposition :: Decomposition
	(
		const Location& location,
		const del :: Comments* comments,
		const value :: Theory theoryName,
		const value :: Signature signatureName,
		const vector :: value :: Symbol& components,
		const bool isStrong
	) :
	location_ (location),
	comments_ (comments),
	theoryName_ (theoryName),
	signatureName_ (signatureName),
	theory_ (Math :: theories()->get (theoryName_)),
	signature_ (Math :: signatures()->get (signatureName_)),
	components_ (components),
	isStrong_ (isStrong) {
	}
	inline
	Decomposition :: Decomposition
	(
		const value :: Theory theoryName,
		const value :: Signature signatureName,
		const bool isStrong
	) :
	location_ (),
	comments_ (NULL),
	theoryName_ (theoryName),
	signatureName_ (signatureName),
	theory_ (Math :: theories()->get (theoryName_)),
	signature_ (Math :: signatures()->get (signatureName_)),
	components_ (INITIAL_COMPONENTS_CAPACITY),
	isStrong_ (isStrong) {
	}
	Decomposition :: ~ Decomposition() {
		deleteAggregateObject (comments_);
	}

using manipulator :: space;
using manipulator :: underline;
using manipulator :: endLine;

	// del :: Decomposition implementation
	bool
	Decomposition :: verify() const
	{
		const value :: Integer size = components_.getSize();
		del :: Theory* component [size];
		for (value :: Integer i = 0; i < size; ++ i) {
			const value :: Theory name = components_ [i];
			const del :: Theory* t = Math :: theories()->get (name);
			const del :: Theory* th = t->clone();
			component [i] = const_cast<del :: Theory*>(th);
		}
		Theory* unionTheory = new Theory (value :: undefined :: THEORY);
		for (value :: Integer i = 0; i < size; ++ i) {
			unionTheory->unite (component [i]);
		}
		del :: Theory*
			minimalTheory = theory_->clone();
		minimalTheory->minimize();
		//unionTheory->repair();
		const bool result = minimalTheory->isEquivalent (unionTheory, true);
		for (value :: Integer i = 0; i < size; ++ i) {
			component [i]->commitSuicide();
		}
		minimalTheory->commitSuicide();
		unionTheory->commitSuicide();
		return result;
	}
	void
	Decomposition :: addComponent (const value :: Signature component) {
		components_.add (component);
	}
	bool
	Decomposition :: isEqual (const del :: Decomposition* dec) const
	{
		const Decomposition*
			decomposition = dynamic_cast<const Decomposition*>(dec);
		const value :: Integer
			size = decomposition->components_.getSize();
		if (components_.getSize() != size) {
			return false;
		}
		if (isStrong_) {
			return isEqualTheoryDecomposition (decomposition);
		} else {
			return isEqualSignatureDecomposition (decomposition);
		}
	}
	value :: Integer
	Decomposition :: getSize() const {
		return components_.getSize();
	}
	value :: Symbol
	Decomposition :: getComponent (const value :: Integer index) const {
		return components_.getValue (index);
	}
	void
	Decomposition :: replicateCompletely (String& string) const
	{
		string << "/****************************************/" << endLine;
		string << "/*            decomposition             */" << endLine;
		string << "/****************************************/" << endLine;
		string << endLine;
		string << "// Theory:" << endLine;
		theory_->replicate (string);
		string << endLine;
		string << "// Delta:" << endLine;
		signature_->replicate (string);
		string << endLine;
		string << "// Signatures:" << endLine;
		for (value :: Integer i = 0; i < components_.getSize(); ++ i) {
			const value :: Symbol
				name = components_.getValue (i);
			const del :: Signature*
				signature = Math :: signatures()->get (name);
			signature->replicate (string);
			string << endLine;
		}
		string << "// Decomposition:" << endLine;
		replicate (string);
	}

	// object :: Writable implementation
	void
	Decomposition :: replicate (String& string) const
	{
		if (comments_ != NULL) {
			comments_->replicate (string);
		}
		string << location_.getIndent();
		string << Token :: decompositionOf_ << space;
		if (isStrong_) {
			string << Token :: theory_ << space;
		} else {
			string << Token :: signature_ << space;
		}
		string << Token :: openBracket_;
		string << Table :: theories()->get (theoryName_);
		string << Token :: comma_ << space;
		string << Table :: signatures()->get (signatureName_);
		string << Token :: closeBracket_ << space << Token :: equality_ << space;

		const value :: Integer size = components_.getSize();

		if (size >1) {
			string << Token :: openBracket_;
		}
		if (size > 0) {
			for (value :: Integer i = 0; i < size - 1; ++ i) {
				if (isStrong_) {
					const value :: Theory
						component = components_.getValue (i);
					string << Table :: theories()->get (component);
				} else {
					const value :: Signature
						component = components_.getValue (i);
					string << Table :: signatures()->get (component);
				}
				string << space << Token :: union_ << space;
			}
			if (isStrong_) {
				const value :: Theory
					lastComponent = components_.getLastValue();
				string << Table :: theories()->get (lastComponent);
			} else {
				const value :: Signature
					lastComponent = components_.getLastValue();
				string << Table :: signatures()->get (lastComponent);
			}
		}
		if (size >1) {
			string << Token :: closeBracket_;
		}
		string << endLine;
		string << endLine;
	}
	void
	Decomposition :: translate (String& string) const {
		replicate (string);
	}
	void
	Decomposition :: write (String& string) const
	{
		if (Config :: removeComments()) {
			string << "/****************************************/" << endLine;
			string << "/*            decomposition             */" << endLine;
			string << "/****************************************/" << endLine;
			string << endLine;
		}
		//signature_->replicate (string);
		//theory_->replicate (string);
		/*if (isStrong_) {
			for (value :: Integer i = 0; i < components_.getSize(); ++ i) {
				const value :: Theory
					name = components_.getValue (i);
				const del :: Theory*
					theory = Math :: theories()-> get (name);
				theory->replicate (string);
			}
		} else {
			for (value :: Integer i = 0; i < components_.getSize(); ++ i) {
				const value :: Signature
					name = components_.getValue (i);
				const del :: Signature*
					signature = Math :: signatures()-> get (name);
				signature->replicate (string);
			}
		}*/
		replicate (string);
		string << endLine << endLine;
	}

	// object :: Object implementation
	void
	Decomposition :: commitSuicide() {
		delete this;
	}
	Size_t
	Decomposition :: getSizeOf() const {
		return sizeof (Decomposition);
	}
	Size_t
	Decomposition :: getVolume() const
	{
		Size_t volume = 0;
		volume += getAggregateVolume (comments_);
		volume += components_.getVolume();
		return volume;
	}

	/****************************
	 *		Private members
	 ****************************/

	bool
	Decomposition :: isEqualTheoryDecomposition (const Decomposition* decomposition) const
	{
		for (value :: Integer i = 0; i < components_.getSize(); ++ i) {
			const value :: Theory
				name_1 = components_.getValue (i);
			const del :: Theory*
				theory_1 = Math :: theories()-> get (name_1);
			bool contains = false;
			for (value :: Integer j = 0; j < components_.getSize(); ++ j) {
				const value :: Theory
					name_2 = decomposition->components_.getValue (j);
				const del :: Theory*
					theory_2 = Math :: theories()-> get (name_2);
				if (theory_1->isEqual (theory_2)) {
					contains = true;
					break;
				}
			}
			if (!contains) {
				return false;
			}
		}
		return true;
	}
	bool
	Decomposition :: isEqualSignatureDecomposition (const Decomposition* decomposition) const
	{
		for (value :: Integer i = 0; i < components_.getSize(); ++ i) {
			const value :: Signature
				name_1 = components_.getValue (i);
			const del :: Signature*
				signature_1 = Math :: signatures()-> get (name_1);
			bool contains = false;
			for (value :: Integer j = 0; j < components_.getSize(); ++ j) {
				const value :: Signature
					name_2 = decomposition->components_.getValue (j);
				const del :: Signature*
					signature_2 = Math :: signatures()-> get (name_2);
				if (signature_1->isEqual (signature_2)) {
					contains = true;
					break;
				}
			}
			if (!contains) {
				return false;
			}
		}
		return true;
	}

}
}


