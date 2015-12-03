/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_misc_Path.hpp                                       */
/* Description:     path in the filesystem                                   */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef NSTD_MISC_PATH_HPP_
#define NSTD_MISC_PATH_HPP_

namespace nstd {
namespace misc {

template<class A>
class Path :
	public Object,
	public memory :: storage :: Scalar<Path<A>, A> {
public :
	typedef A Allocator_;
	typedef String<Allocator_> String_;
	typedef Size_t Depth_;
	typedef typename String_ :: Index_ Index_;
	enum {
		NO,
		DIR,
		DOT,
		DOUBLE_DOT
	};

	Path();
	Path (const Path&);
	template<class A1>
	Path (const Path<A1>&);
	template<class A1>
	Path (const String<A1>&);
	Path (const char*);
	virtual ~ Path();

	void parse (const char*);

	char& prefix();
	String_& name();
	String_& directory (const Depth_);
	String_& extension();
	String_& pushDirectory();
	template<class A1>
	void pushDirectoryFirst (const String<A1>&);
	template<class A1>
	void pushDirectoryLast (const String<A1>&);
	void pushDirectoryFirst (const char*);
	void pushDirectoryLast (const char*);
	String_* popDirectoryFirst();
	String_* popDirectoryLast();

	char getPrefix() const;
	Depth_ getDepth() const;
	const String_& getString() const;
	const String_& getName() const;
	const String_& getExtension() const;
	const String_& getDirectory (const Depth_) const;

	bool isDefined() const;
	bool isUndefined() const;
	bool extensionIs (const char*) const;
	bool isFile() const;
	bool isDirectory() const;
	void provideDirectory() const;
	void showInDetails (std :: ostream&) const;

	// Path "../../dir_1/dir_2/dir_3/file.xxx" converts to "dir_3/file.xxx"
	void reduceUpDirectories();
	// from Path "../../dir_1/dir_2/dir_3/file.xxx" returns 2
	Depth_ getUpDirectoriesCount() const;
	// Path "dir_1/file.xxx" with depth =2 converts to "../../dir_1/file.xxx"
	void insertUpDirectories (Depth_);

	template<class A1>
	bool operator == (const Path<A1>&) const;
	template<class A1>
	bool operator != (const Path<A1>&) const;

	template<class A1>
	void copy (const Path<A1>&);

	// nstd :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String<>&) const;

private :
	template<class>
	friend class Path;

	typedef
		container :: Vector
		<
			String_,
			container :: storage :: ByPointer,
			Allocator_
		>
		Directories_;

	const char* parsePrefix();
	const char* parseDirectories();
	const char* parseExtension();
	void parsePath ();
	void buildPath () const;
	void checkPath (const char*) const;

	mutable bool changed_;
	mutable String_ path_;

	char    prefix_;
	String_ extension_;
	String_ name_;
	Directories_ directories_;
};

}
}

#endif /*NSTD_MISC_PATH_HPP_*/
