/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_source_Signature.cpp                                 */
/* Description:     signature class                                          */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "del/interface/del_interface.hpp"

namespace del {
namespace source {

	/****************************
	 *		Public members
	 ****************************/

	template<class A>
	Signature<A> :: Signature() :
	location_ (),
	comments_ (NULL),
	name_ (value :: undefined :: SIGNATURE),
	symbols_ (INITIAL_SYMBOLS_CAPACITY) {
	}
	template<class A>
	Signature<A> :: Signature (const value :: Signature name) :
	location_ (),
	comments_ (NULL),
	name_ (name),
	symbols_ (INITIAL_SYMBOLS_CAPACITY) {
	}
	template<class A>
	Signature<A> :: Signature
	(
		const Location& location,
		const del :: Comments* const comments,
		const value :: Signature name
	) :
	location_ (location),
	comments_ (comments),
	name_ (name),
	symbols_ (INITIAL_SYMBOLS_CAPACITY) {
		Math :: signatures()->add (this);
	}
	template<class A>
	Signature<A> :: Signature (const Signature& signature) :
	location_ (signature.location_),
	comments_ (NULL),
	name_ (signature.name_),
	symbols_ (signature.symbols_) {
	}
	template<class A>
	Signature<A> :: Signature (const del :: Signature* signature) :
	location_ (),
	comments_ (NULL),
	name_ (signature->getName()),
	symbols_ (signature->cardinality())
	{
		for (value :: Integer i = 0; i < signature->cardinality(); ++ i) {
			const del :: Symbol& symbol = signature->getSymbol (i);
			addSymbol (symbol);
		}
	}
	template<class A>
	Signature<A> :: ~ Signature() {
		deleteAggregateObject (comments_);
	}

	template<class A>
	typename Signature<A> :: Signature*
	Signature<A> :: createRandom ()
	{
		const value :: Integer conceptCount = Config :: getSigmaConceptCount();
		const value :: Integer relationCount = Config :: getSigmaRelationCount();
		return createRandom (conceptCount, relationCount);
	}
	template<class A>
	typename Signature<A> :: Signature*
	Signature<A> :: createRandom
	(
		const value :: Integer conceptCount,
		const value :: Integer relationCount
	)
	{
		const value :: Signature name = Table :: signatures()->fresh ("sig");
		Signature* signature = new Signature (name);
		for (value :: Integer i = 0; i < conceptCount; ++ i) {
			const value :: Symbol c = Table :: variables()->fresh ("c");
			const Symbol concept (c, false);
			signature->addSymbol (concept);
		}
		for (value :: Integer i = 0; i < relationCount; ++ i) {
			const value :: Relation r = Table :: relations()->fresh ("r");
			const Symbol relation (r, true);
			signature->addSymbol (relation);
		}
		return signature;
	}

	// del :: Signature implementation
	template<class A>
	value :: Integer
	Signature<A> :: getSize() const {
		return symbols_.getSize();
	}
	template<class A>
	bool
	Signature<A> :: isEqual (const del :: Signature* signature) const
	{
		const value :: Integer
			size = signature->cardinality();
		if (symbols_.getSize() != size) {
			return false;
		}
		for (value :: Integer i = 0; i < symbols_.getSize(); ++ i) {
			const del :: Symbol
				symbol = symbols_.getValue (i);
			if (!signature->containsSymbol (symbol)) {
				return false;
			}
		}
		return true;
	}
	template<class A>
	bool
	Signature<A> :: isSubset (const del :: Signature* signature) const
	{
		const value :: Integer
			size = signature->cardinality();
		for (value :: Integer i = 0; i < symbols_.getSize(); ++ i) {
			const del :: Symbol&
				symbol = symbols_.getReference (i);
			if (symbol.isTop() || symbol.isUndefined()) {
				continue;
			}
			if (!signature->containsSymbol (symbol)) {
				return false;
			}
		}
		return true;
	}
	template<class A>
	void
	Signature<A> :: copy (const del :: Signature* signature)
	{
		const Signature*
			sign = dynamic_cast<const Signature*>(signature);
		name_ = sign->name_;
		symbols_.copy (sign->symbols_);
	}
	template<class A>
	void
	Signature<A> :: clear() {
		symbols_.clear();
	}
	template<class A>
	value :: Signature
	Signature<A> :: getName() const {
		return name_;
	}
	template<class A>
	void
	Signature<A> :: setName (const value :: Signature name) {
		name_ = name;
	}
	template<class A>
	value :: Integer
	Signature<A> :: cardinality() const {
		return symbols_.getSize();
	}
	template<class A>
	const del :: Symbol&
	Signature<A> :: getSymbol (const value :: Integer i) const {
		return symbols_.getReference (i);
	}
	template<class A>
	const del :: Symbol&
	Signature<A> :: getRandomSymbol() const
	{
		const value :: Integer i = rand() % symbols_.getSize();
		return symbols_.getReference (i);
	}
	template<class A>
	const del :: Symbol&
	Signature<A> :: getRandomConcept() const
	{
		value :: Integer conceptCount = 0;
		for (value :: Integer i = 0; i < symbols_.getSize(); ++ i) {
			if (symbols_.getReference (i).isVariable()) {
				++ conceptCount;
			}
		}
		const value :: Integer index = rand() % conceptCount;
		value :: Integer c = 0;
		for (value :: Integer i = 0; i < symbols_.getSize(); ++ i) {
			if (symbols_.getReference (i).isVariable()) {
				if (c == index) {
					return symbols_.getReference (i);
				} else {
					++ c;
				}
			}
		}
		return symbols_.getReference (0);
	}
	template<class A>
	const del :: Symbol&
	Signature<A> :: getRandomRelation() const
	{
		value :: Integer relationCount = 0;
		for (value :: Integer i = 0; i < symbols_.getSize(); ++ i) {
			if (symbols_.getReference (i).isRelation()) {
				++ relationCount;
			}
		}
		const value :: Integer index = rand() % relationCount;
		value :: Integer c = 0;
		for (value :: Integer i = 0; i < symbols_.getSize(); ++ i) {
			if (symbols_.getReference (i).isRelation()) {
				if (c == index) {
					return symbols_.getReference (i);
				} else {
					++ c;
				}
			}
		}
		return symbols_.getReference (0);
	}

	template<class A>
	void
	Signature<A> :: makeDeltaCopy (const del :: Expansion* expansion)
	{
		for (value :: Integer i = 0; i < symbols_.getSize(); ++ i) {
			const del :: Symbol&
				symbol = symbols_.getReference (i);
			const del :: Symbol
				newSymbol = expansion->addPostfixToSymbol(symbol); //expansion->newSymbol (symbol);
			symbols_.getReference (i) = newSymbol;
		}
	}
	template<class A>
	bool
	Signature<A> :: containsSymbol (const del :: Symbol& symbol) const {
		return symbols_.contains (symbol);
	}
	template<class A>
	void
	Signature<A> :: addSymbol (const del :: Symbol& symbol) {
		symbols_.add (symbol);
	}
	template<class A>
	void
	Signature<A> :: removeSymbol (const del :: Symbol& symbol) {
		symbols_.removeValue (symbol);
	}
	template<class A>
	void
	Signature<A> :: intersect (const del :: Signature* signature)
	{
		const Signature& sign = dynamic_cast<const Signature&>(*signature);
		symbols_.intersect (sign.symbols_);
	}
	template<class A>
	void
	Signature<A> :: join (const del :: Signature* signature)
	{
		const Signature& sign = dynamic_cast<const Signature&>(*signature);
		symbols_.unite (sign.symbols_);
	}
	template<class A>
	void
	Signature<A> :: subtract (const del :: Signature* signature)
	{
		const Signature& sign = dynamic_cast<const Signature&>(*signature);
		symbols_.subtract (sign.symbols_);
	}

	// del :: Cloneable implementation
	template<class A>
	del :: Signature*
	Signature<A> :: clone() const
	{
		if (this == NULL) {
			return NULL;
		} else {
			return new Signature (*this);
		}
	}

using manipulator :: endLine;
using manipulator :: space;
using manipulator :: iterate;
using manipulator :: tab;

	// object :: Writable implementation
	template<class A>
	void
	Signature<A> :: replicate (String& string) const
	{
		if (comments_ != NULL) {
			comments_->replicate (string);
		}
		string << location_.getIndent();
		string << Token :: signature_ << space;
		if (name_ != value :: undefined :: SIGNATURE) {
			string << Table :: signatures()->get (name_) << space;
			string << Token :: equality_ << space;
		}
		string << Token :: openBrace_ << endLine;
		if (symbols_.getSize() > 0) {
			for (value :: Integer i = 0; i < symbols_.getSize() - 1; ++ i) {
				const del :: Symbol& symbol = symbols_.getReference (i);
				string << location_.getIndent() << tab;
				if (symbol.isRelation()) {
					string << Token :: relation_ << manipulator :: space;
				} else {
					string << Token :: concept_ << manipulator :: space;
				}
				string << symbol << Token :: comma_ << endLine;
			}
			const del :: Symbol& symbol = symbols_.getLastReference();
			string << location_.getIndent() << tab;
			if (symbol.isRelation()) {
				string << Token :: relation_ << manipulator :: space;
			} else {
				string << Token :: concept_ << manipulator :: space;
			}
			string << symbol << endLine;
		}
		string << Token :: closeBrace_ << endLine;
		string << endLine;
	}
	template<class A>
	void
	Signature<A> :: translate (String& string) const {
		replicate (string);
	}

	// del :: Object implementation
	template<class A>
	void
	Signature<A> :: commitSuicide() {
		delete this;
	}
	template<class A>
	Size_t
	Signature<A> :: getVolume() const
	{
		Size_t volume = 0;
		volume += getAggregateVolume (comments_);
		volume += symbols_.getVolume();
		return volume;
	}
	template<class A>
	Size_t
	Signature<A> :: getSizeOf() const {
		return sizeof (Signature);
	}
	template<class A>
	void
	Signature<A> :: show (String& string) const
	{
		//replicate (string);
		string << Token :: signature_ << space;
		if (name_ != value :: undefined :: SIGNATURE) {
			string << Table :: signatures()->get (name_) << space;
			string << Token :: equality_ << space;
		}
		string << Token :: openBrace_;
		if (symbols_.getSize() > 0) {
			for (value :: Integer i = 0; i < symbols_.getSize() - 1; ++ i) {
				string << symbols_.getReference (i) << Token :: comma_ << space;
			}
			string << symbols_.getLastValue();
		}
		string << Token :: closeBrace_<< space;
	}
}
}


