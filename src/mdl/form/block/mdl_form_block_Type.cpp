/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_form_block_Type.cpp                                  */
/* Description:     type class                                               */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_FORM_BLOCK_TYPE_CPP_
#define MDL_FORM_BLOCK_TYPE_CPP_

namespace mdl {
namespace form {
namespace block {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Type :: Type
	(
		const Location& location,
		const mdl :: Comments* comments,
		value :: Name name,
		const vector :: parser :: Identificator& superNames,
		mdl :: Theory* theory
	) :
	form :: Identifiable (location, comments, name, theory),
	index_ (Math :: types()->add (this)),
	superNames_ (superNames),
	supers_ (superNames.getSize()),
	subTypes_ (),
	ruleTree_ (new tree :: Rule())
	{
		if (Config :: localParsing()) {
			return;
		}
		theory_->addComponent (this);
		form :: Identifiable :: build();
		for (index :: Type i = 0; i < superNames_.getSize(); ++ i) {
			mdl :: Identificator*
				name = superNames_.getValue (i);
			mdl :: Super*
				super = new form :: block :: Super (this, name, theory);
			supers_.add (super);
		}
		try {
			for (index :: Type i = 0; i < supers_.getSize(); ++ i) {
				mdl :: Super*
					super = supers_.getValue (i);
				super->build();
				super->addSuperSuper (supers_);
			}
			theory_->addName (index_, name_);
		} catch (Error* error) {
			error->add (location_);
			throw error;
		}
	}
	Type :: ~ Type() {
		deleteAggregateObject (ruleTree_);
	}

using nstd :: manipulator :: underline;
using nstd :: manipulator :: iterate;
using nstd :: manipulator :: tab;
using nstd :: manipulator :: endLine;

	// mdl :: Type implementation
	void
	Type :: mine (String& string, const index :: Type depth) const
	{
		if (subTypes_.isEmpty()) {
			string << iterate << depth << tab << "<type ";
			Identifiable :: mine (string);
			string << "/>" << endLine;
			return;
		}
		string << iterate << depth << tab << "<type ";
		Identifiable :: mine (string);
		string << ">" << endLine;
		for (value :: Integer i = 0; i < subTypes_.getSize(); ++ i){
			const mdl :: Type* const
				type = subTypes_.getValue (i);
			type->mine (string, depth + 1);
		}
		string << iterate << depth << tab;
		string << "</type>" << endLine;
	}
	index :: Type
	Type :: getSuperCount() const {
		return supers_.getSize();
	}
	index :: Type
	Type :: getInferCount() const {
		return subTypes_.getSize();
	}
	bool
	Type :: isSuper (const mdl :: Type* const type) const
	{
		if (type == this) {
			return true;
		}
		for (index :: Type i = 0; i < supers_.getSize(); ++ i) {
			if (supers_.getValue (i)->getType() == type) {
				return true;
			}
		}
		return false;
	}
	bool
	Type :: isInfer (const mdl :: Type* const type) const
	{
		if (type == this) {
			return true;
		}
		for (index :: Type i = 0; i < subTypes_.getSize(); ++ i) {
			if (subTypes_.getValue (i) == type) {
				return true;
			}
		}
		return false;
	}

	void
	Type :: addRule (mdl :: Rule* rule) {
		ruleTree_->addBranch (rule->getTerm()->getExpression(), rule);
	}
	void
	Type :: addSubtype (mdl :: Type* type)
	{
		if (subTypes_.contains (type)) {
			return;
		}
		subTypes_.add (type);
		for (index :: Type i = 0; i < supers_.getSize(); ++ i) {
			mdl :: Type*
				superType = supers_.getValue (i)->getType();
			superType->addSubtype (type);
		}
	}

	tree :: Rule*
	Type :: getRuleTree() {
		return ruleTree_;
	}
	mdl :: Super*
	Type :: getSuper (const index :: Type index) {
		return supers_.getValue (index);
	}
	mdl :: Super*
	Type :: getSuper (const mdl :: Type* const type)
	{
		mdl :: Super* super = NULL;
		for (index :: Type i = 0; i < supers_.getSize(); ++ i) {
			super = supers_.getValue(i);
			if (super->getType() == type) {
				return super;
			}
		}
		return NULL;
	}
	mdl :: Type*
	Type :: getInfer (const index :: Type index) {
		return subTypes_.getValue (index);
	}

	const tree :: Rule*
	Type :: getRuleTree() const {
		return ruleTree_;
	}
	const mdl :: Super*
	Type :: getSuper (const index :: Type index) const {
		return supers_.getValue (index);
	}
	const  mdl :: Super*
	Type :: getSuper (const mdl :: Type* const type) const
	{
		const mdl :: Super* super = NULL;
		for (index :: Type i = 0; i < supers_.getSize(); ++ i) {
			super = supers_.getValue(i);
			if (super->getType() == type) {
				return super;
			}
		}
		return NULL;
	}
	const  mdl :: Type*
	Type :: getInfer (const index :: Type index) const {
		return subTypes_.getValue (index);
	}

	// object :: Identifiable interface
	const Location&
	Type :: getLocation() const {
		return Identifiable :: getLocation();
	}
	value :: Name
	Type :: getName() const {
		return Identifiable :: getName();
	}
	void
	Type :: translateName (String& string, const index :: Arity i) const {
		Identifiable :: translateName (string, i);
	}
	void
	Type :: replicateName (String& string) const {
		Identifiable :: replicateName (string);
	}
	mdl :: Theory*
	Type :: getTheory() {
		return Identifiable :: getTheory();
	}
	mdl :: Identificator*
	Type :: getIdentificator() {
		return Identifiable :: getIdentificator();
	}
	const mdl :: Theory*
	Type :: getTheory() const {
		return Identifiable :: getTheory();
	}
	const mdl :: Identificator*
	Type :: getIdentificator() const {
		return Identifiable :: getIdentificator();
	}

using manipulator :: space;
using manipulator :: tab;
using manipulator :: endLine;
using manipulator :: iterate;

	// object :: Verifiable implementation
	void
	Type :: mine (String& string) const
	{
		if (!Config :: getMiningOptions().getValue (Config :: MINE_TYPES)) {
			return;
		}
		const value :: Integer depth =
			Config :: getMiningOptions().getValue (Config :: MINE_THEORIES) ?
			Identifiable :: getDepth() :
			1;
		string << iterate << depth << tab << "<type ";
		Identifiable :: mine (string);
		string << "/>" << endLine;
	}

	// object :: Buildable implementation
	void
	Type :: build() {
	}

	// object :: Writable implementation
	void
	Type :: translate (String& string) const
	{
		if (!Config :: removeComments() && (comments_ != NULL)) {
			string << location_.getIndent();
			comments_->translate (string);
			string << endLine;
		}
		string << location_.getIndent() << :: smm :: Token :: constant_ << space;
		Identifiable :: translateName (string);
		string << space << :: smm :: Token :: end_ << endLine;
		string << endLine;
		for (index :: Type i = 0; i < supers_.getSize(); ++ i) {
			const mdl :: Super* const
				super = supers_.getValue (i);
			super->translate (string);
		}
		string << endLine;
	}
	void
	Type :: replicate (String& string) const
	{
		if (!Config :: removeComments() && (comments_ != NULL)) {
			string << location_.getIndent();
			comments_->replicate (string);
			string << endLine;
		}
		string << location_.getIndent() << Token :: type_ << space;
		Identifiable :: replicateName (string);
		string << space;
		if (superNames_.isEmpty()) {
			string << Token :: semicolon_ << endLine;
		} else {
			string << Token :: colon_ <<  space;
			for (index :: Type i = 0; i < superNames_.getSize(); ++ i) {
				const mdl :: Identificator* const
					superName = superNames_.getValue (i);
				superName->replicate (string);
				if (i < superNames_.getSize() - 1) {
					string << Token :: comma_ << space;
				}
			}
			string << Token :: semicolon_ << endLine;
		}
		string << endLine;
	}
	bool
	Type :: lookup() const
	{
		if (location_.isNearestTo (Config :: getPosition())) {
			return true;
		}
		for (index :: Type i = 0; i < superNames_.getSize(); ++ i) {
			const mdl :: Identificator* const
				superName = superNames_.getValue (i);
			if (superName->lookup()) {
				const mdl :: Super* super = supers_.getValue(i);
				const mdl :: Type* superType = super->getType();
				if (Config :: lookupDefinition()) {
					std :: cout << *superType;
				} else {
					std :: cout << superType->getLocation();
				}
				return true;
			}
		}
		return false;
	}
	object :: Writable*
	Type :: find()
	{
		if (location_.isNearestTo (Config :: getPosition())) {
			return this;
		}
		for (index :: Type i = 0; i < superNames_.getSize(); ++ i) {
			mdl :: Identificator*
				superName = superNames_.getValue (i);
			if (superName->lookup()) {
				mdl :: Super* super = supers_.getValue(i);
				mdl :: Type* superType = super->getType();
				return superType;
			}
		}
		return NULL;
	}
	const object :: Writable*
	Type :: find() const
	{
		if (location_.isNearestTo (Config :: getPosition())) {
			return this;
		}
		for (index :: Type i = 0; i < superNames_.getSize(); ++ i) {
			const mdl :: Identificator* const
				superName = superNames_.getValue (i);
			if (superName->lookup()) {
				const mdl :: Super* super = supers_.getValue(i);
				const mdl :: Type* superType = super->getType();
				return superType;
			}
		}
		return NULL;
	}

	// object :: Object implementation
	void
	Type :: commitSuicide() {
		delete this;
	}
	Size_t
	Type :: getVolume() const {
		Size_t volume = 0;
		volume += Identifiable :: getVolume();
		volume += superNames_.getVolume();
		volume += supers_.getVolume();
		volume += subTypes_.getVolume();
		volume += getAggregateVolume (ruleTree_);
		return volume;
	}
	Size_t
	Type :: getSizeOf() const {
		return sizeof (Type);
	}
}
}
}

#endif /*MDL_FORM_BLOCK_TYPE_CPP_*/
