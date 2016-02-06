/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_auxiliary_Log.cpp                                    */
/* Description:     log class                                                */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

namespace del {
namespace auxiliary {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Log :: Log() :
	stream_ (),
	path_ (),
	message_ (),
	initialized_ (false),
	pathName_ ()
	{
		for (int i = 0; i < MESSAGE_COUNT; ++ i) {
			message_ [i] = NULL;
			path_ [i] = NULL;
			pathName_ [i] = NULL;
		}
	}
	Log :: ~ Log() {
		destroy();
	}

	bool
	Log :: init (const char* path)
	{
		if (initialized_) {
			return false;
		}
		pathName_ [DECOMPOSITION_LOG] = "decomposition.log";
		pathName_ [REDUNDANT_AXIOMS_LOG] = "redundant_axioms.log";
		pathName_ [AUTOMATIC_DELTA_LOG] = "delta-threshold.log";
		for (int i = 0; i < MESSAGE_COUNT; ++ i) {
			message_ [i] = new String (INITIAL_MESSAGE_CAPACITY);
			if (pathName_ [i] == NULL) {
				path_ [i] = new Path (path);
				path_ [i]->name() << "_" << i;
			} else {
				path_ [i] = new Path (pathName_ [i]);
			}
		}
		initialized_ = true;
		return true;
	}
	bool
	Log :: init (const String& path)
	{
		if (initialized_) {
			return false;
		}
		pathName_ [DECOMPOSITION_LOG] = "decomposition.log";
		pathName_ [REDUNDANT_AXIOMS_LOG] = "redundant_axioms.log";
		pathName_ [AUTOMATIC_DELTA_LOG] = "delta-threshold.log";
		for (int i = 0; i < MESSAGE_COUNT; ++ i) {
			message_ [i] = new String (INITIAL_MESSAGE_CAPACITY);
			if (pathName_ [i] == NULL) {
				path_ [i] = new Path (path);
				path_ [i]->name() << "_" << i;
			} else {
				path_ [i] = new Path (pathName_ [i]);
			}
		}
		initialized_ = true;
		return true;
	}
	bool
	Log :: init()
	{
		if (initialized_) {
			return false;
		}
		for (int i = 0; i < MESSAGE_COUNT; ++ i) {
			message_ [i] = new String (INITIAL_MESSAGE_CAPACITY);
		}
		initialized_ = true;
		return true;
	}
	void
	Log :: destroy()
	{
		if (!initialized_) {
			return;
		}
		for (int i = 0; i < MESSAGE_COUNT; ++ i) {
			delete message_ [i];
			message_ [i] = NULL;
			delete path_ [i];
			path_ [i] = NULL;
			pathName_ [i] = NULL;
		}
		initialized_ = false;
	}

	inline String&
	Log :: message (const int i) {
		return *message_ [i];
	}

	void
	Log :: show (const int i, std :: ostream& os) const
	{
		if (!initialized_) {
			return;
		}
		if (message_ [i]->isEmpty()) {
			return;
		}
		if (SHOW_HEADER) {
			os << "LOG: ";
			if (pathName_ [i] == NULL) {
				os << i;
			} else {
				os << pathName_ [i];
			}
			os << " BEGIN" << std :: endl;
			os << "----------------------" << std :: endl;
		}
		os << *message_ [i] << std :: endl;
		if (SHOW_HEADER) {
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
		for (int i = 0; i < MESSAGE_COUNT; ++ i) {
			if ((i == 0) && (Config :: getLog().isUndefined())) {
				continue;
			}
			show (i, os);
		}
	}
	void
	Log :: write (const int i, std :: ostream& os) const
	{
		if (!initialized_) {
			return;
		}
		if (path_ [i] == NULL) {
			show (i, os);
		} else {
			if (message_ [i]->isEmpty()) {
				return;
			}
			open (i);
			show (i, stream_ [i]);
			close (i);
		}
	}
	void
	Log :: write (std :: ostream& os) const
	{
		for (int i = 0; i < MESSAGE_COUNT; ++ i) {
			if ((i == 0) && (Config :: getLog().isUndefined())) {
				continue;
			}
			write (i, os);
		}
	}
	inline void
	Log :: clear()
	{
		if (!initialized_) {
			return;
		}
		for (int i = 0; i < MESSAGE_COUNT; ++ i) {
			if (message_ [i] != NULL) {
				message_ [i]->clear();
			}
		}
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
		for (int i = 0; i < MESSAGE_COUNT; ++ i) {
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
		if (!initialized_) {
			return;
		}
		for (int i = 0; i < MESSAGE_COUNT; ++ i) {
			if (message_ [i]->isEmpty()) {
				continue;
			}
			if (SHOW_HEADER) {
				string << "LOG: ";
				if (pathName_ [i] == NULL) {
					string << i;
				} else {
					string << pathName_ [i];
				}
				string << " BEGIN" << endLine;
				string << "----------------------" << endLine;
			}
			string << *message_ [i] << endLine;
			message_ [i]->clear();
			if (SHOW_HEADER) {
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

	inline void
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
	inline void
	Log :: close (const int i) const
	{
		stream_ [i].flush();
		stream_ [i].close();
	}
}
}


