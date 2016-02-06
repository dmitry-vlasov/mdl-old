/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_auxiliary_Log.hpp                                    */
/* Description:     log class                                                */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "mdl/interface/mdl_interface.hpp"

namespace mdl {
namespace auxiliary {

class Log :
	public object :: Object,
	public Scalar<Log, allocator :: Heap>{
public :
	Log();
	virtual ~ Log();

	enum {
		DEFAULT  = 0,
		CHECKER  = 1,
		PROVER   = 2,
		GRAPH    = 3,
		COMPRESS = 4,
		MAXIMUM  = 5,
		LOG_COUNT = MAXIMUM + 1
	};

	String& message (const int = DEFAULT);

	void show (const int, std :: ostream& = std :: cout) const;
	void show (std :: ostream& = std :: cout) const;
	void write (const int) const;
	void write () const;
	void clear();

	void setName (const int, const String&);
	void setName (const int, const char*);

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	enum {
		INITIAL_MESSAGE_CAPACITY = 1024 * 4
	};
	void open (const int) const;
	void close (const int) const;

	bool used_;
	mutable OutputFileStream stream_ [LOG_COUNT];
	Path* path_ [LOG_COUNT];
	mutable String* message_ [LOG_COUNT];
	const char* pathName_ [LOG_COUNT];
	bool showHeader_ [LOG_COUNT];
};

}
}


