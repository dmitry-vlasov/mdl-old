/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_config_Config.cpp                                   */
/* Description:     resulting config class                                   */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef NSTD_CONFIG_CONFIG_CPP_
#define NSTD_CONFIG_CONFIG_CPP_

namespace nstd {
namespace config {

	/****************************
	 *		Public members
	 ****************************/

using std :: cout;
using std :: endl;

	template<class C>
	template<class S>
	void
	Config<C> :: showUsageMessage (S& os, const List& list)
	{
		General :: showUsageMessage (os, list);
		MemoryInfo  :: showUsageMessage (os, list);
		ProgramInfo :: showUsageMessage (os, list);
		Paths   :: showUsageMessage (os, list);
	}
	template<class C>
	template<class S>
	void
	Config<C> :: showOptionValues (S& os, const List& list)
	{
		General :: showOptionValues (os, list);
		MemoryInfo  :: showOptionValues (os, list);
		ProgramInfo :: showOptionValues (os, list);
		Paths   :: showOptionValues (os, list);
	}
	template<class C>
	template<class S>
	void
	Config<C> :: showGroupNames (S& os)
	{
		General :: showGroupName (os);
		MemoryInfo  :: showGroupName (os);
		ProgramInfo :: showGroupName (os);
		Paths   :: showGroupName (os);
	}

	/****************************
	 *		Protected members
	 ****************************/

	template<class C>
	bool
	Config<C> :: proceedOptions
	(
		const int argCount,
		const char* argValues[]
	)
	{
		const int firstIndex = inExternalConfig_ ? 0 : 1;
		const int lastIndex  = inExternalConfig_ ? argCount - 1 : argCount - 2;
		for (int i = firstIndex; i <= lastIndex; ++ i) {
			const char* opt = argValues [i];
			if (*opt == '-') {
				++ opt;
			} else {
				exit_ = true;
				error_ = true;
				return false;
			}
			if (*opt == '-') {
				++ opt;
				if (!Config_ :: proceedStringOption (opt, argCount, argValues, i)) {
					std :: cout << "unknown option: \"" << opt << "\"" << std :: endl;
					exit_ = true;
					error_ = true;
					return false;
				}
			} else if (!Config_ :: proceedOneCharOption (opt, argCount, argValues, i)) {
				std :: cout << "unknown option: \"" << opt << "\"" << std :: endl;
				exit_ = true;
				error_ = true;
				return false;
			}
		}
		if (!inExternalConfig_) {
			int lastIndex = argCount - 1;
			const char* lastOption = argValues [lastIndex];
			if (*lastOption == '-') {
				bool result = true;
				++ lastOption;
				if (*lastOption == '-') {
					++ lastOption;
					result = Config_ :: proceedStringOption (lastOption, argCount, argValues, lastIndex);
				} else {
					result = Config_ :: proceedOneCharOption (lastOption, argCount, argValues, lastIndex);
				}
				if (!result) {
					std :: cout << "unknown option: \"" << lastOption << "\"" << std :: endl;
					exit_ = true;
					error_ = true;
				}
				return result;
			} else {
				Paths :: proceedLastOption (lastOption);
			}
		}
		while (!Paths :: getConfigVector()->isEmpty()) {
			Paths :: Path_* config = Paths :: configVector()->popFirst();
			String<> path (config->getString());
			delete config;
			if (!proceedFile (path.c_str())) {
				return false;
			}
		}
		return true;
	}
	template<class C>
	bool
	Config<C> :: proceedFile (const char* fileName)
	{
		const Size_t size = nstd :: system :: getFileSize (fileName);
		char buffer [size + 2];
		buffer [0] = chars :: NULL_CHAR;
		buffer [size + 1] = chars :: NULL_CHAR;
		nstd :: InputFileStream fileStream;
		fileStream.open (fileName);
		fileStream.read (buffer + 1, size);
		fileStream.close();
		const int argCount = countArguments (size, buffer + 1);
		const char* argValues [argCount];
		evalArguments (size, buffer + 1, argValues);
		const bool status = inExternalConfig_;
		inExternalConfig_ = true;
		const bool result = proceedOptions (argCount, argValues);
		inExternalConfig_ = status;
		return result;
	}
	template<class C>
	int
	Config<C> :: countArguments (const int size, const char buffer[])
	{
		int argCount = 0;
		bool inComment = false;
		for (int i = 0; i < size; ++ i) {
			if (buffer [i] == chars :: HASH_KEY) {
				inComment = true;
			}
			if (buffer [i] == chars :: NEW_LINE) {
				inComment = false;
			}
			if (!inComment &&
				!isWhitespace (buffer [i]) &&
				isWhitespace (buffer [i + 1])) {
				++ argCount;
			}
		}
		return argCount;
	}
	template<class C>
	void
	Config<C> :: evalArguments (const int size, char buffer[], const char* argValues [])
	{
		int argCount = 0;
		bool inComment = false;
		for (int i = 0; i < size; ++ i) {
			if (buffer [i] == chars :: HASH_KEY) {
				inComment = true;
			}
			if (buffer [i] == chars :: NEW_LINE) {
				inComment = false;
			}
			if (!inComment &&
				!isWhitespace (buffer [i]) &&
				isWhitespace (buffer [i + 1])) {
				buffer [i + 1] = chars :: NULL_CHAR;
			}
			if (!inComment &&
				!isWhitespace (buffer [i]) &&
				isWhitespace (buffer [i - 1])) {
				argValues [argCount ++] = buffer + i;
			}
		}
	}
	template<class C>
	inline bool
	Config<C> :: isWhitespace (const char c)
	{
		return
			(c == chars :: SPACE) ||
			(c == chars :: TAB) ||
			(c == chars :: NEW_LINE) ||
			(c == chars :: NULL_CHAR);
	}

	template<class C>
	void 
	Config<C> :: init()
	{
		General :: init();
		MemoryInfo :: init();
		Paths :: init();
		ProgramInfo :: init();
	}
	template<class C>
	void
	Config<C> :: release()
	{
		General :: release();
		MemoryInfo :: release();
		Paths :: release();
		ProgramInfo :: release();
	}
	template<class C>
	Size_t
	Config<C> :: getVolume()
	{
		Size_t volume = 0;
		volume += General :: getVolume();
		volume += MemoryInfo :: getVolume();
		volume += Paths :: getVolume();
		volume += ProgramInfo :: getVolume();
		return volume;
	}

	template<class C>
	bool
	Config<C> :: proceedStringOption (const char* opt, const int argCount, const char* argValues[], int& i)
	{
		if (General :: proceedStringOption (opt, argCount, argValues, i)) {
			return true;
		}
		if (MemoryInfo :: proceedStringOption (opt, argCount, argValues, i)) {
			return true;
		}
		if (ProgramInfo :: proceedStringOption (opt, argCount, argValues, i)) {
			return true;
		}
		if (Paths :: proceedStringOption (opt, argCount, argValues, i)) {
			return true;
		}
		return false;
	}

using std :: cout;
using std :: endl;

	template<class C>
	bool
	Config<C> :: proceedOneCharOption (const char* opt, const int argCount, const char* argValues[], int& i)
	{
		if (opt [1] != '\0') {
			cout << "option which starts with a single \"-\" must be one character." << endl;
			cout << "option: \"" << opt << "\" consists of more then one character." << endl;
			exit_ = true;
			error_ = true;
			return false;
		}
		if (General :: proceedOneCharOption (opt, argCount, argValues, i)) {
			return true;
		}
		if (MemoryInfo :: proceedOneCharOption (opt, argCount, argValues, i)) {
			return true;
		}
		if (ProgramInfo :: proceedOneCharOption (opt, argCount, argValues, i)) {
			return true;
		}
		if (Paths :: proceedOneCharOption (opt, argCount, argValues, i)) {
			return true;
		}
		return false;
	}
}
}

#endif /*NSTD_CONFIG_CONFIG_CPP_*/
