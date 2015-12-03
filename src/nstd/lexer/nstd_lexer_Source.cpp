/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_lexer_Source.cpp                                    */
/* Description:     input source                                             */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef NSTD_LEXER_SOURCE_CPP_
#define NSTD_LEXER_SOURCE_CPP_

namespace nstd {
namespace lexer {

	/****************************
	 *		Public members
	 ****************************/

	template<int S>
	template<class A>
	inline
	Source<S> :: Source (const String<A>& fileName, const bool isTop) :
	fileName_ (fileName.c_str()),
	isTop_ (isTop),
	location_ (this),
	buffer_ (),
	charStart_ (),
	charStop_ (),
	charCurrent_ (),
	insideIndent_ (true) {
	}
	template<int S>
	Source<S> :: ~ Source () {
	}

	template<int S>
	inline bool
	Source<S> :: open (const char* fileName)
	{
		fileName_ = fileName;
		return open();
	}
	template<int S>
	bool
	Source<S> :: open() {
		if (fileName_ == NULL) {
			return false;
		}
		if (!buffer_.open (fileName_)) {
			return false;
		}
		location_.position().start();
		buffer_.setInitial (charCurrent_.char_);
		startToken();
		stopToken();
		return true;
	}
	template<int S>
	bool
	Source<S> :: isTop() const {
		return isTop_;
	}
	template<int S>
	inline void
	Source<S> :: close()
	{
		location_.position().clear();
		location_.indent().clear();
		buffer_.close();
	}
	template<int S>
	inline bool
	Source<S> :: isEmpty() const {
		return (buffer_.getFileSize() == 0);
	}
	template<int S>
	inline const char*
	Source<S> :: file() const {
		return fileName_;
	}

	template<int S>
	void
	Source<S> :: operator ++ ()
	{
		location_.position_.incColumn();
		location_.position_.incIndex();

		switch (charCurrent_.getValue()) {
		case chars :: NEW_LINE :
			location_.newLine();
			insideIndent_ = true;
			break;
		case chars :: SPACE :
			if (insideIndent_) {
				location_.indent_.incSpaces();
			}
			break;
		case chars :: TAB :
			if (insideIndent_) {
				location_.indent_.incTabs();
			}
			break;
		}
		if (!charCurrent_.isWhitespace()) {
			insideIndent_ = false;
		}

		++ charCurrent_;
		reserve();
	}
	template<int S>
	void
	Source<S> :: reserve (const Size_t dist)
	{
		if (buffer_.checkEnd (charCurrent_.char_, dist)) {
			++ buffer_;
			buffer_.shiftBack (charStart_);
			buffer_.shiftBack (charStop_);
			buffer_.shiftBack (charCurrent_.char_);
		}
	}
	template<int S>
	inline void
	Source<S> :: setTop (const bool isTop) {
		isTop_ = isTop;
	}

	template<int S>
	inline void
	Source<S> :: startToken() {
		charStart_ = charCurrent_.char_;
	}
	template<int S>
	inline void
	Source<S> :: stopToken() {
		charStop_ = charCurrent_.char_;
	}

	template<int S>
	inline Char
	Source<S> :: getChar() const {
		return charCurrent_;
	}
	template<int S>
	inline const char*
	Source<S> :: getTokenStart() const {
		return charStart_;
	}
	template<int S>
	inline const char*
	Source<S> :: getTokenStop() const {
		return charStop_;
	}
	template<int S>
	inline const typename Source<S> :: Location_&
	Source<S> :: getLocation() const {
		return location_;
	}
	template<int S>
	const typename Source<S> :: Buffer_&
	Source<S> :: getBuffer() const {
		return buffer_;
	}
	template<int S>
	inline typename Source<S> :: Location_&
	Source<S> :: location() {
		return location_;
	}

using manipulator :: endLine;
using manipulator :: space;

	template<int S>
	template<class T>
	inline void
	Source<S> :: show (T& string) const {
		string << "file:" << space << fileName_  << endLine;
	}

	// nstd :: Object implementation
	template<int S>
	void
	Source<S> :: commitSuicide() {
		delete this;
	}
	template<int S>
	Size_t
	Source<S> :: getVolume() const
	{
		Size_t volume = 0;
		volume += location_.getVolume();
		volume += charCurrent_.getVolume();
		volume += buffer_.getVolume();
		return volume;
	}
	template<int S>
	Size_t
	Source<S> :: getSizeOf() const {
		return sizeof (Source);
	}
	template<int S>
	void
	Source<S> :: show (String<>& string) const {
		string << "file:" << space << fileName_  << endLine;
	}
}
}

#endif /*NSTD_LEXER_SOURCE_CPP_*/
