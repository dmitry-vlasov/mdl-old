/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_auxiliary_Log.cpp                                    */
/* Description:     log class                                                */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_AUXILIARY_LOG_CPP_
#define MDL_AUXILIARY_LOG_CPP_

namespace mdl {
namespace auxiliary {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Log :: Log() :
	used_ (false),
	stream_ (),
	path_ (),
	message_ (),
	pathName_ (),
	showHeader_ ()
	{
		pathName_ [DEFAULT]  = "mdl.log";
		pathName_ [CHECKER]  = "checker.log";
		pathName_ [PROVER]   = "prover.log";
		pathName_ [GRAPH]    = "graph.gml";
		pathName_ [COMPRESS] = "compress.log";
		for (int i = 0; i < LOG_COUNT; ++ i) {
			message_ [i] = new String (INITIAL_MESSAGE_CAPACITY);
			showHeader_ [i] = false;
			if (pathName_ [i] == NULL) {
				path_ [i] = new Path ("mdl_log");
				path_ [i]->name() << "_" << i;
			} else {
				path_ [i] = new Path (pathName_ [i]);
			}
		}
	}
	Log :: ~ Log()
	{
		for (int i = 0; i < LOG_COUNT; ++ i) {
			delete message_ [i];
			message_ [i] = NULL;
			delete path_ [i];
			path_ [i] = NULL;
			pathName_ [i] = NULL;
		}
	}

	inline String&
	Log :: message (const int i)
	{
		used_ = true;
		return *message_ [i];
	}

	void
	Log :: show (const int i, std :: ostream& os) const
	{
		if (message_ [i]->isEmpty()) {
			return;
		}
		if (showHeader_ [i]) {
			os << "LOG: ";
			if (pathName_ [i] == NULL) {
				os << i;
			} else {
				os << pathName_ [i];
			}
			os << " BEGIN" << std :: endl;
			os << "----------------------" << std :: endl;
		}
		os << *message_ [i];
		if (showHeader_ [i]) {
			os << std :: endl;
			os << "LOG: ";
			if (pathName_ [i] == NULL) {
				os << i;
			} else {
				os << pathName_ [i];
			}
			os << " END" << std :: endl;
			os << "----------------------" << std :: endl;
			os << std :: endl;
		}
		message_ [i]->clear();
	}
	void
	Log :: show (std :: ostream& os) const
	{
		for (int i = 0; i < LOG_COUNT; ++ i) {
			show (i, os);
		}
	}
	void
	Log :: write (const int i) const
	{
		if (path_ [i] != NULL) {
			if (message_ [i]->isEmpty()) {
				return;
			}
			open (i);
			show (i, stream_ [i]);
			close (i);
		}
	}
	void
	Log :: write() const
	{
		if (!used_) {
			return;
		}
		for (int i = 0; i < LOG_COUNT; ++ i) {
			if (message_ [i]->isEmpty()) {
				continue;
			}
			open (i);
			show (i, stream_ [i]);
			close (i);
		}
	}
	void
	Log :: clear()
	{
		for (int i = 0; i < LOG_COUNT; ++ i) {
			if (message_ [i] != NULL) {
				message_ [i]->clear();
			}
		}
	}

	void
	Log :: setName (const int i, const String& name)
	{
		pathName_ [i] = name.c_str();
		if (path_ [i] != NULL) {
			path_ [i]->commitSuicide();
		}
		path_ [i] = new Path (pathName_ [i]);
	}
	void
	Log :: setName (const int i, const char* name)
	{
		pathName_ [i] = name;
		if (path_ [i] != NULL) {
			path_ [i]->commitSuicide();
		}
		path_ [i] = new Path (pathName_ [i]);
	}

using manipulator :: space;
using manipulator :: tab;
using manipulator :: endLine;

	// object :: Object implementation
	inline void
	Log :: commitSuicide() {
		delete this;
	}
	inline Size_t
	Log :: getVolume() const
	{
		Size_t volume = 0;
		for (int i = 0; i < LOG_COUNT; ++ i) {
			volume += getAggregateVolume (message_ [i]);
			volume += getAggregateVolume (path_ [i]);
		}
		return volume;
	}
	inline Size_t
	Log :: getSizeOf() const {
		return sizeof (Log);
	}
	inline void
	Log :: show (String& string) const
	{
		if (!used_) {
			return;
		}
		for (int i = 0; i < LOG_COUNT; ++ i) {
			if (message_ [i]->isEmpty()) {
				continue;
			}
			if (showHeader_ [i]) {
				string << "LOG: ";
				if (pathName_ [i] == NULL) {
					string << i;
				} else {
					string << pathName_ [i];
				}
				string << " BEGIN" << endLine;
				string << "----------------------" << endLine;
			}
			string << *message_ [i];
			message_ [i]->clear();
			if (showHeader_ [i]) {
				string << endLine;
				string << "LOG: ";
				if (pathName_ [i] == NULL) {
					string << i;
				} else {
					string << pathName_ [i];
				}
				string << " END" << endLine;
				string << "----------------------" << endLine;
				string << endLine;
			}
		}
	}

	/****************************
	 *		Private members
	 ****************************/

	void
	Log :: open (const int i) const
	{
		const char* const
			outputPath = path_ [i]->getString().c_str();
		stream_ [i].open (outputPath, std :: ios :: binary);
		if (!stream_ [i].is_open()) {
			Error* error = new Error (Error :: OUTPUT);
			error->message() << "cannot open log file: " << *path_ [i] << " for output" << endLine;
			throw error;
		}
	}
	void
	Log :: close (const int i) const
	{
		stream_ [i].flush();
		stream_ [i].close();
	}
}
}

#endif /*MDL_AUXILIARY_LOG_CPP_*/
