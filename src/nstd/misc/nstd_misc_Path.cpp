/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_misc_Path.cpp                                       */
/* Description:     path in the filesystem                                   */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef NSTD_MISC_PATH_CPP_
#define NSTD_MISC_PATH_CPP_

namespace nstd {
namespace misc {

	/****************************
	 *		Public members
	 ****************************/

	template<class A>
	inline
	Path<A> :: Path () :
	changed_ (true),
	path_(),
	prefix_ (NO),
	extension_(),
	name_(),
	directories_() {
	}
	template<class A>
	inline
	Path<A> :: Path (const Path& path) :
	changed_ (path.changed_),
	path_(path.getString()),
	prefix_ (path.prefix_),
	extension_(path.getExtension()),
	name_(path.getName()),
	directories_(path.getDepth())
	{
		for (Depth_ depth = 0; depth < path.getDepth(); ++ depth) {
			String_* dir_1 = directories_.push();
			const String_& dir_2 = path.getDirectory (depth);
			dir_1->copy (dir_2);
		}
	}
	template<class A>
	template<class A1>
	inline
	Path<A> :: Path (const Path<A1>& path) :
	changed_ (path.changed_),
	path_(path.getString()),
	prefix_ (path.getPrefix()),
	extension_(path.getExtension()),
	name_(path.getName()),
	directories_(path.getDepth())
	{
		for (Depth_ depth = 0; depth < path.getDepth(); ++ depth) {
			String_* dir_1 = directories_.push();
			const String<A1>& dir_2 = path.getDirectory (depth);
			dir_1->copy (dir_2);
		}
	}
	template<class A>
	template<class A1>
	inline
	Path<A> :: Path (const String<A1>& path) :
	changed_ (false),
	path_ (path),
	prefix_ (NO),
	extension_(),
	name_(),
	directories_ ()
	{
		parsePath ();
		buildPath ();
		checkPath (path.c_str());
	}
	template<class A>
	inline
	Path<A> :: Path (const char* path) :
	changed_ (false),
	path_ (path),
	prefix_ (NO),
	extension_(),
	name_(),
	directories_ ()
	{
		parsePath ();
		buildPath ();
		checkPath (path);
	}
	template<class A>
	Path<A> :: ~ Path() {
	}

	template<class A>
	void
	Path<A> :: parse (const char* path)
	{
		changed_ = true;
		path_ = path;
		parsePath ();
		buildPath ();
		checkPath (path);
	}

	template<class A>
	inline char&
	Path<A> :: prefix() {
		changed_ = true;
		return prefix_;
	}
	template<class A>
	inline typename Path<A> :: String_&
	Path<A> :: name() {
		changed_ = true;
		return name_;
	}
	template<class A>
	inline typename Path<A> :: String_&
	Path<A> :: directory (const Depth_ depth) {
		changed_ = true;
		return *(directories_.getValue (depth));
	}
	template<class A>
	inline typename Path<A> :: String_&
	Path<A> :: extension() {
		changed_ = true;
		return extension_;
	}
	template<class A>
	inline typename Path<A> :: String_&
	Path<A> :: pushDirectory () {
		changed_ = true;
		return *directories_.push();
	}
	template<class A>
	template<class A1>
	inline void
	Path<A> :: pushDirectoryFirst (const String<A1>& directory)
	{
		String_* newDirectory = directories_.pushFirst();
		newDirectory->copy (directory);
		changed_ = true;
	}
	template<class A>
	template<class A1>
	inline void
	Path<A> :: pushDirectoryLast (const String<A1>& directory)
	{
		String_* newDirectory = directories_.pushLast();
		newDirectory->copy (directory);
		changed_ = true;
	}
	template<class A>
	inline void
	Path<A> :: pushDirectoryFirst (const char* directory)
	{
		String_* newDirectory = directories_.pushFirst();
		newDirectory->copy (directory);
		changed_ = true;
	}
	template<class A>
	inline void
	Path<A> :: pushDirectoryLast (const char* directory)
	{
		String_* newDirectory = directories_.pushLast();
		newDirectory->copy (directory);
		changed_ = true;
	}
	template<class A>
	inline typename Path<A> :: String_*
	Path<A> :: popDirectoryFirst() {
		return directories_.popFirst();
	}
	template<class A>
	inline typename Path<A> :: String_*
	Path<A> :: popDirectoryLast() {
		return directories_.popLast();
	}

	template<class A>
	inline char
	Path<A> :: getPrefix() const {
		return prefix_;
	}
	template<class A>
	inline Size_t
	Path<A> :: getDepth() const {
		return directories_.getSize();
	}
	template<class A>
	inline const typename Path<A> :: String_&
	Path<A> :: getString() const
	{
		if (changed_) {
			buildPath();
		}
		return path_;
	}
	template<class A>
	inline const typename Path<A> :: String_&
	Path<A> :: getName() const {
		return name_;
	}
	template<class A>
	inline const typename Path<A> :: String_&
	Path<A> :: getExtension() const {
		return extension_;
	}
	template<class A>
	inline const typename Path<A> :: String_&
	Path<A> :: getDirectory (const Depth_ depth) const {
		return *(directories_.getValue (depth));
	}

	template<class A>
	inline bool
	Path<A> :: isDefined() const {
		return !isUndefined();
	}
	template<class A>
	inline bool
	Path<A> :: isUndefined() const {
		const String_& string = getString();
		return string.isEmpty();
	}
	template<class A>
	inline bool
	Path<A> :: extensionIs (const char* extension) const {
		return (extension_ == extension);
	};
	template<class A>
	inline bool
	Path<A> :: isFile() const {
		return !name_.isEmpty();
	}
	template<class A>
	inline bool
	Path<A> :: isDirectory() const {
		return name_.isEmpty() && extension_.isEmpty();
	}
	template<class A>
	void
	Path<A> :: provideDirectory() const
	{
		if (changed_) {
			buildPath ();
		}
		const char* const dir = path_.c_str();
		char* ch = path_.c_str();
		switch (prefix_) {
		case DOUBLE_DOT : ++ ch;
		case DOT : ++ ch;
		case DIR : ++ ch;
		default :  break;
		}
		while (*ch != chars :: NULL_CHAR) {
			if (*ch == chars :: DIR_DELIMITER) {
				*ch = chars :: NULL_CHAR;
				system :: createDirectory (dir);
				*ch = chars :: DIR_DELIMITER;
			}
			++ ch;
		}
	}
	template<class A>
	void
	Path<A> :: showInDetails (std :: ostream& os) const
	{
		os << "changed_ = " << (changed_ ? "true" : "false") << std :: endl;
		os << "path_ = " << path_ << std :: endl;
		os << "prefix_ = ";
		switch (prefix_) {
		case NO :
			os << "" << std :: endl; break;
		case DIR :
			os << chars :: DIR_DELIMITER << std :: endl; break;
		case DOT :
			os << chars :: DOT << std :: endl; break;
		case DOUBLE_DOT :
			os << chars :: DOT << chars :: DOT << std :: endl; break;
		}
		os << "extension_ = " << extension_ << std :: endl;
		os << "name_ = " << name_ << std :: endl;
		os << "directories_ = " << std :: endl;
		for (Depth_ d = 0; d < directories_.getSize(); ++ d) {
			const String_* directory = directories_.getValue (d);
			os << '\t' << *directory << std :: endl;
		}
		os << std :: endl;
	}

	template<class A>
	void
	Path<A> :: reduceUpDirectories()
	{
		Depth_ counterUp = getUpDirectoriesCount();
		Depth_ reducedIndex = counterUp * 2;
		if (prefix_ == DOUBLE_DOT) {
			-- reducedIndex;
			prefix_ = NO;
		}
		for (Depth_ i = 0; i < directories_.getSize(); ++ i) {
			String_* directory_i = directories_.getValue (i);
			const Depth_ j = i + reducedIndex;
			if (j < directories_.getSize()) {
				String_* directory_j = directories_.getValue (j);
				directory_i->copy (*directory_j);
			} else {
				directories_.getLastValue()->commitSuicide();
				directories_.removeLast();
			}
		}
		buildPath();
	}
	template<class A>
	typename Path<A> :: Depth_
	Path<A> :: getUpDirectoriesCount() const
	{
		Depth_ counterUp = (prefix_ == DOUBLE_DOT) ? 1 : 0;
		for (Depth_ i = 0; i < directories_.getSize(); ++ i) {
			const String_* directory = directories_.getValue (i);
			if (
				(directory->getSize() != 2) ||
				(directory->getValue (0) != chars :: DOT) ||
				(directory->getValue (1) != chars :: DOT)
				) {
				break;
			} else {
				++ counterUp;
			}
		}
		return counterUp;
	}
	template<class A>
	void
	Path<A> :: insertUpDirectories (Depth_ count)
	{
		if (count > 0) {
			prefix_ = DOUBLE_DOT;
			-- count;
		}
		for (Depth_ d = 0; d < count; ++ d) {
			pushDirectoryFirst ("..");
		}
		buildPath();
	}

	template<class A>
	template<class A1>
	inline bool
	Path<A> :: operator == (const Path<A1>& path) const
	{
		if (changed_) {
			buildPath ();
		}
		return (path_ == path.path_);
	}
	template<class A>
	template<class A1>
	inline bool
	Path<A> :: operator != (const Path<A1>& path) const {
		return !(operator == (path));
	}
	template<class A>
	template<class A1>
	inline void
	Path<A> :: copy (const Path<A1>& path)
	{
		changed_   = path.changed_;
		path_      = path.path_;
		name_      = path.name_;
		extension_ = path.extension_;

		for (Depth_ depth = 0; depth < directories_.getSize(); ++ depth) {
			String_*& dir_1 = directories_.getReference(depth);
			dir_1->commitSuicide();
			dir_1 = NULL;
		}
		directories_.clear();
		for (Depth_ depth = 0; depth < path.getDepth(); ++ depth) {
			String_* dir_1 = directories_.push();
			const String_& dir_2 = path.getDirectory (depth);
			dir_1->copy (dir_2);
		}
	}

	// nstd :: Object implementation
	template<class A>
	void
	Path<A> :: commitSuicide() {
		delete this;
	}
	template<class A>
	Size_t
	Path<A> :: getVolume() const
	{
		Size_t result = 0;
		result += path_.getVolume();
		result += name_.getVolume();
		result += extension_.getVolume();
		result += directories_.getVolume();
		return result;
	}
	template<class A>
	Size_t
	Path<A> :: getSizeOf() const {
		return sizeof (Path);
	}
	template<class A>
	void
	Path<A> :: show (String<>& string) const
	{
		if (changed_) {
			buildPath();
		}
		string << path_;
	}

	/****************************
	 *		Private members
	 ****************************/

	template<class A>
	const char*
	Path<A> :: parsePrefix()
	{
		const char* const initialChar = path_.getFirstChar();
		const char ch0 = initialChar [0];
		if (ch0 == chars :: DIR_DELIMITER) {
			prefix_ = DIR;
			return initialChar + 1;
		}
		if (ch0 != chars :: DOT) {
			prefix_ = NO;
			return initialChar;
		}
		const char ch1 = initialChar [1];
		if (ch1 == chars :: DIR_DELIMITER) {
			prefix_ = DOT;
			return initialChar + 2;
		}
		if (ch1 != chars :: DOT) {
			prefix_ = NO;
			return initialChar;
		}
		const char ch2 = initialChar [2];
		if (ch2 == chars :: DIR_DELIMITER) {
			prefix_ = DOUBLE_DOT;
			return initialChar + 3;
		}
		prefix_ = NO;
		return initialChar;
	}
	template<class A>
	const char*
	Path<A> :: parseDirectories ()
	{
		directories_.clear();

		const char* const initialChar = parsePrefix();
		const char* const terminalChar = path_.getTerminalChar();

		const char* firstChar = initialChar;
		for (const char* ch = initialChar; ch != terminalChar; ++ ch)
		{
			if (*ch == chars :: DIR_DELIMITER) {
				String_* dir = directories_.push();
				dir->copyFrom (firstChar, ch);
				firstChar = ch + 1;
			}
		}
		return firstChar;
	}
	template<class A>
	const char*
	Path<A> :: parseExtension ()
	{
		const char* const initial = path_.getFirstChar();
		const char* const terminal = path_.getTerminalChar();

		const char* delimiter = terminal - 1;
		while (delimiter != initial) {
			if (*delimiter == chars :: EXTENSION_DELIMITER) {
				break;
			}
			-- delimiter;
		}
		if (delimiter == initial) {
			return terminal;
		} else {
			extension_.copyFrom (delimiter + 1, terminal);
			return delimiter;
		}
	}
	template<class A>
	void
	Path<A> :: parsePath()
	{
		const char* const initialNameChar = parseDirectories();
		const char* const terminalNameChar = parseExtension();
		name_.copyFrom (initialNameChar, terminalNameChar);
	}
	template<class A>
	void
	Path<A> :: buildPath() const
	{
		path_.clear();
		switch (prefix_) {
		case DIR :
			path_ << chars :: DIR_DELIMITER;
			break;
		case DOT :
			path_ << chars :: DOT << chars :: DIR_DELIMITER;
			break;
		case DOUBLE_DOT :
			path_ << chars :: DOT << chars :: DOT << chars :: DIR_DELIMITER;
			break;
		case NO :
		default :
			break;
		}
		for (Depth_ depth = 0; depth < getDepth(); ++ depth) {
			const String_* dir = directories_.getValue (depth);
			path_ << *dir << chars :: DIR_DELIMITER;
		}
		path_ << name_;
		if (!extension_.isEmpty()) {
			path_ << chars :: EXTENSION_DELIMITER;
			path_ << extension_;
		}
		changed_ = false;
	}
	template<class A>
	void
	Path<A> :: checkPath (const char* path) const
	{
		const typename String_ :: Index_
			length = String_ :: getStringLength (path);
		if (length != path_.getSize()) {
			goto bad;
		}
		for (typename String_ :: Index_ i = 0; i < length; ++ i) {
			if (path_ [i] != path [i]) {
				goto bad;
			}
		}
		return;
		bad :
			std :: cout << "path " << path_ << " was parsed incorrectly" << std :: endl;
			std :: cout << "parse result: " << path_ << std :: endl;
			throw std :: exception();
	}
}
}

#endif /*NSTD_MISC_PATH_CPP_*/
