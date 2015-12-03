/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_form_block_Constant.cpp                              */
/* Description:     constant class                                           */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_FORM_BLOCK_CONSTANT_CPP_
#define MDL_FORM_BLOCK_CONSTANT_CPP_

namespace mdl {
namespace form {
namespace block {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Constant :: Constant
	(
		const Location& location,
		const mdl :: Comments* const comments,
		String* symbol,
		String* ascii,
		String* latex,
		mdl :: Theory* theory
	) :
	form :: Identifiable
	(
		location,
		comments,
		value :: undefined :: NAME,
		theory
	),
	symbol_ (symbol),
	ascii_ (ascii),
	latex_ (latex),
	literal_ (Table :: literals()->add (symbol, ascii, latex))
	{
		if (Config :: localParsing()) {
			return;
		}
		Math :: constants()->add (this);
		theory_->addComponent (this);
	}
	Constant :: ~ Constant()
	{
		deleteAggregateObject (symbol_);
		deleteAggregateObject (ascii_);
		deleteAggregateObject (latex_);
	}

	// mdl :: Constant implementation
	index :: Literal
	Constant :: getSize() const {
		return 1;
	}
	value :: Literal
	Constant :: getValue (const index :: Literal index) const {
		return literal_;
	}

	// object :: Identifiable interface
	const Location&
	Constant :: getLocation() const {
		return Identifiable :: getLocation();
	}
	value :: Name
	Constant :: getName() const {
		return Identifiable :: getName();
	}
	void
	Constant :: translateName (String& string, const index :: Arity i) const {
	}
	void
	Constant :: replicateName (String& string) const {
	}
	mdl :: Theory*
	Constant :: getTheory() {
		return Identifiable :: getTheory();
	}
	mdl :: Identificator*
	Constant :: getIdentificator() {
		return Identifiable :: getIdentificator();
	}
	const mdl :: Theory*
	Constant :: getTheory() const {
		return Identifiable :: getTheory();
	}
	const mdl :: Identificator*
	Constant :: getIdentificator() const {
		return Identifiable :: getIdentificator();
	}

using nstd :: manipulator :: endLine;
using nstd :: manipulator :: space;
using nstd :: manipulator :: tab;
using nstd :: manipulator :: iterate;

	// object :: Verifiable implementation
	/*void
	Constant :: check() {
	}
	void
	Constant :: compress() {
	}
	void
	Constant :: reprove() {
	}
	void
	Constant :: prove() {
	}
	bool
	Constant :: isVerified() const {
		return true;
	}*/
	void
	Constant :: mine (String& string) const
	{
		if (!Config :: getMiningOptions().getValue (Config :: MINE_CONSTANTS)) {
			return;
		}
		const value :: Integer depth =
			Config :: getMiningOptions().getValue (Config :: MINE_THEORIES) ?
			Identifiable :: getDepth() :
			1;
		string << iterate << depth << tab << "<constant ";
		string << "name=\""; writeXMLSafe (string); string << "\" ";
		Identifiable :: mine (string);
		string << "/>" << endLine;
	}

	// object :: Buildable implementation
	void
	Constant :: build() {
	}

	// object :: Writable implementation
	void
	Constant :: translate (String& string) const
	{
		if (!Config :: removeComments() && (comments_ != NULL)) {
			string << location_.getIndent();
			comments_->translate (string);
			string << endLine;
		}
		string << location_.getIndent();
		string << :: smm :: Token :: constant_ << space;
		string << *Table :: literals()->getAscii (literal_) << space;
		string << :: smm :: Token :: end_ << endLine;
		string << endLine;
	}
	void
	Constant :: replicate (String& string) const
	{
		if (!Config :: removeComments() && (comments_ != NULL)) {
			string << location_.getIndent();
			comments_->replicate (string);
			string << endLine;
		}
		string << location_.getIndent() << Token :: constant_ << space << endLine;
		string << location_.getIndent() << Token :: openBrace_ << space << endLine;

		string << location_.getIndent() << tab << Token :: symbol_ << space;
		string << *symbol_ << space << Token :: semicolon_ << endLine;;

		if (ascii_ != NULL) {
			string << location_.getIndent() << tab << Token :: ascii_ << space;
			string << *ascii_ << space << Token :: semicolon_ << endLine;;
		}
		if (latex_ != NULL) {
			string << location_.getIndent() << tab << Token :: latex_ << space;
			string << *latex_ << space << Token :: semicolon_ << endLine;;
		}
		string << location_.getIndent() << Token :: closeBrace_ << space << endLine;
		string << endLine;
	}
	bool
	Constant :: lookup() const
	{
		if (location_.isNearestTo (Config :: getPosition())) {
			return true;
		} else {
			return false;
		}
	}
	object :: Writable*
	Constant :: find()
	{
		if (location_.isNearestTo (Config :: getPosition())) {
			return this;
		} else {
			return NULL;
		}
	}
	const object :: Writable*
	Constant :: find() const
	{
		if (location_.isNearestTo (Config :: getPosition())) {
			return this;
		} else {
			return NULL;
		}
	}

	// object :: Object implementation
	void
	Constant :: commitSuicide() {
		delete this;
	}
	Size_t
	Constant :: getVolume() const
	{
		Size_t volume = 0;
		volume += form :: Identifiable :: getVolume();
		volume += getAggregateVolume (symbol_);
		volume += getAggregateVolume (ascii_);
		volume += getAggregateVolume (latex_);
		return volume;
	}
	Size_t
	Constant :: getSizeOf() const {
		return sizeof (Constant);
	}

	/****************************
	 *		Private members
	 ****************************/

	void
	Constant :: writeXMLSafe (String& string) const
	{
		for (value :: Integer i = 0; i < symbol_->getSize(); ++ i) {
			const char ch = symbol_->getValue (i);
			switch (ch) {
			case '\"' :
				string << "&quot;";
				break;
			case '\'' :
				string << "&apos;";
				break;
			case '&' :
				string << "&amp;";
				break;
			case '<' :
				string << "&lt;";
				break;
			case '>' :
				string << "&gt;";
				break;
			default :
				string << ch;
			}
		}
	}
}
}
}

#endif /*MDL_FORM_BLOCK_CONSTANT_CPP_*/
