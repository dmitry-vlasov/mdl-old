/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_lexer_Location.cpp                                  */
/* Description:     location in input                                        */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef NSTD_LEXER_LOCATION_CPP_
#define NSTD_LEXER_LOCATION_CPP_

namespace nstd {
namespace lexer {

	/****************************
	 *		Public members
	 ****************************/

	template<class S>
	inline
	Location<S> :: Location() :
	source_ (NULL),
	indent_ (),
	position_ (),
	node_ (NULL) {
	}
	template<class S>
	inline
	Location<S> :: Location (const Indent indent) :
	source_ (NULL),
	indent_ (indent),
	position_ (),
	node_ (NULL) {
	}
	template<class S>
	inline
	Location<S> :: Location (const Source_* const source) :
	source_ (source),
	indent_ (),
	position_ (),
	node_ (NULL) {
	}
	template<class S>
	inline
	Location<S> :: Location (const Location& location) :
	source_ (location.source_),
	position_ (location.position_),
	indent_ (location.indent_),
	node_ (location.node_) {
	}

	template<class S>
	inline Position&
	Location<S> :: position() {
		return position_;
	}
	template<class S>
	inline Indent&
	Location<S> :: indent() {
		return indent_;
	}
	template<class S>
	inline const Position&
	Location<S> :: getPosition() const {
		return position_;
	}
	template<class S>
	inline const Indent&
	Location<S> :: getIndent() const {
		return indent_;
	}
	template<class S>
	inline bool
	Location<S> :: isTop() const {
		return source_->isTop();
	}
	template<class S>
	inline const char*
	Location<S> :: file() const {
		return source_->file();
	}

	template<class S>
	inline bool
	Location<S> :: operator == (const Location& location) const
	{
		return
			(source_ == location.source_) &&
			(position_ == location.position_) &&
			(indent_ == location.indent_);
	}
	template<class S>
	inline bool
	Location<S> :: operator != (const Location& location) const {
		return !(operator == (location));
	}
	template<class S>
	inline void
	Location<S> :: operator = (const Location& location)
	{
		source_   = location.source_;
		position_ = location.position_;
		indent_   = location.indent_;
		node_     = location.node_;
	}
	template<class S>
	inline bool
	Location<S> :: isNearestTo (const Position& position) const
	{
		if (node_ == NULL) {
			return false;
		} else {
			if ((node_->prev_ != NULL) && (node_->prev_->position_ > position)) {
				return false;
			}
			if ((node_->next_ != NULL) && (node_->next_->position_ < position)) {
				return false;
			}
			return true;
		}
	}
	template<class S>
	void
	Location<S> :: markupPosition()
	{
		if (source_->isTop()) {
			node_ =  new PositionNode (position_);
		}
	}

	template<class S>
	template<class T>
	inline void
	Location<S> :: show (T& string) const
	{
		if (source_ != NULL) {
			source_->show (string);
		}
		position_.show (string);
	}
	template<class S>
	template<class T>
	inline void
	Location<S> :: showAttributes (T& string) const
	{
		if (source_ != NULL) {
			string << "path=\"" << source_->file() << "\" ";
		}
		string << "line=\"" << position_.getLine() + 1 << "\" ";
		string << "column=\"" << position_.getColumn() + 1 << "\" ";
	}

	template<class S>
	inline Size_t
	Location<S> :: getPositionListVolume()
	{
		Size_t volume = 0;
		PositionNode* node = first_;
		while (node != NULL) {
			volume += sizeof (PositionNode);
			node = node->next_;
		}
		return volume;
	}
	template<class S>
	inline void
	Location<S> :: deletePositionList()
	{
		PositionNode* node = first_;
		while (node != NULL) {
			PositionNode* next = node->next_;
			delete node;
			node = next;
		}
		first_ = NULL;
		last_ = NULL;
	}

	// nstd :: Object implementation
	template<class S>
	void
	Location<S> :: commitSuicide() {
		delete this;
	}
	template<class S>
	Size_t
	Location<S> :: getVolume() const
	{
		Size_t volume = 0;
		volume += position_.getVolume();
		volume += indent_.getVolume();
		return volume;
	}
	template<class S>
	Size_t
	Location<S> :: getSizeOf() const {
		return sizeof (Location);
	}
	template<class S>
	void
	Location<S> :: show (String<>& string) const
	{
		if (source_ != NULL) {
			source_->show (string);
		}
		position_.show (string);
		if (source_ != NULL) {
		}
	}

	/****************************
	 *		Private members
	 ****************************/

	template<class S>
	inline void
	Location<S> :: clear()
	{
		position_.clear();
		indent_.clear();
	}
	template<class S>
	inline void
	Location<S> :: newLine()
	{
		position_.incLine();
		indent_.newLine();
	}

	/*******************************
	 *		PositionNode subclass
	 *******************************/

	template<class S>
	inline
	Location<S> :: PositionNode :: PositionNode (const Position& position) :
	position_ (position),
	prev_ (last_),
	next_ (NULL)
	{
		if (first_ == NULL) {
			first_ = this;
		} else {
			if (last_) {
				last_->next_ = this;
			}
		}
		last_ = this;
	}

	/****************************
	 *		Static members
	 ****************************/

	template<class S>
	typename Location<S> :: PositionNode*
	Location<S> :: first_ = NULL;

	template<class S>
	typename Location<S> :: PositionNode*
	Location<S> :: last_ = NULL;
}
}

#endif /*NSTD_LEXER_LOCATION_CPP_*/
