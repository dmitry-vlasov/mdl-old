/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_auxiliary_Log.hpp                                    */
/* Description:     log class                                                */
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
namespace auxiliary {

class Log :
	public Object,
	public Scalar<Log, allocator :: Heap>{
public :
	Log();
	virtual ~ Log();

	bool init (const char*);
	bool init (const String&);
	bool init ();
	void destroy();

	enum {
		DEFAULT_GENERAL_LOG  = 0,
		DECOMPOSITION_LOG    = 1,
		REDUNDANT_AXIOMS_LOG = 2,
		AUTOMATIC_DELTA_LOG  = 3
	};

	String& message (const int = DEFAULT_GENERAL_LOG);
	void show (const int, std :: ostream& = std :: cout) const;
	void show (std :: ostream& = std :: cout) const;
	void write (const int, std :: ostream& = std :: cout) const;
	void write (std :: ostream& = std :: cout) const;
	void clear();

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	enum {
		SHOW_HEADER = true,
		MESSAGE_COUNT = 8,
		INITIAL_MESSAGE_CAPACITY = 1024 * 4
	};
	void open (const int) const;
	void close (const int) const;

	mutable OutputFileStream stream_ [MESSAGE_COUNT];
	Path* path_ [MESSAGE_COUNT];
	mutable String* message_ [MESSAGE_COUNT];
	bool initialized_;
	const char* pathName_ [MESSAGE_COUNT];
};

}
}


