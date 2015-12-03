/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_config_option_Option.cpp                            */
/* Description:     class for config options                                 */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef NSTD_CONFIG_OPTION_OPTION_CPP_
#define NSTD_CONFIG_OPTION_OPTION_CPP_

namespace nstd {
namespace config {
namespace option {

	/****************************
	 *		Public members
	 ****************************/

	template<>
	inline
	Option<nstd :: Double> :: Option() :
	value_ (Undefined<Type_> :: getValue()),
	name_ (INITIAL_NAME_CAPACITY),
	option_ (INITIAL_OPTION_CAPACITY),
	defaultValue_ (0),
	cmdString_ ("option-real"),
	usageMessage_ (""),
	cmdChar_ (chars :: NULL_CHAR),
	largeIndent_ (DEFAULT_LARGE_INDENT),
	isNameless_ (true),
	sscanfParam_ ("%lf"),
	typeName_ ("<real>"),
	isScaned_ (false),
	isCorrect_ (true) {
	}
	template<>
	inline
	Option<nstd :: U_int64_t> :: Option
	(
		const Type_ defaultValue,
		const char* cmdString,
		const char* usageMessage,
		const char  cmdChar,
		const int   largeIndent
	) :
	value_ (defaultValue),
	name_ (cmdString),
	option_ (INITIAL_OPTION_CAPACITY),
	defaultValue_ (defaultValue),
	cmdString_ (cmdString),
	usageMessage_ (usageMessage),
	cmdChar_ (cmdChar),
	largeIndent_ (largeIndent),
	isNameless_ (false),
	sscanfParam_ ("%d"),
	typeName_ ("<size>"),
	isScaned_ (false),
	isCorrect_ (true) {
	}
	template<>
	inline
	Option<nstd :: Int64_t> :: Option
	(
		const Type_ defaultValue,
		const char* cmdString,
		const char* usageMessage,
		const char  cmdChar,
		const int   largeIndent
	) :
	value_ (defaultValue),
	name_ (cmdString),
	option_ (INITIAL_OPTION_CAPACITY),
	defaultValue_ (defaultValue),
	cmdString_ (cmdString),
	usageMessage_ (usageMessage),
	cmdChar_ (cmdChar),
	largeIndent_ (largeIndent),
	isNameless_ (false),
	sscanfParam_ ("%d"),
	typeName_ ("<size>"),
	isScaned_ (false),
	isCorrect_ (true) {
	}
	template<>
	inline
	Option<nstd :: Double> :: Option
	(
		const Type_ defaultValue,
		const char* cmdString,
		const char* usageMessage,
		const char  cmdChar,
		const int   largeIndent
	) :
	value_ (defaultValue),
	name_ (cmdString),
	option_ (INITIAL_OPTION_CAPACITY),
	defaultValue_ (defaultValue),
	cmdString_ (cmdString),
	usageMessage_ (usageMessage),
	cmdChar_ (cmdChar),
	largeIndent_ (largeIndent),
	isNameless_ (false),
	sscanfParam_ ("%lf"),
	typeName_ ("<real>"),
	isScaned_ (false),
	isCorrect_ (true) {
	}
	template<>
	inline
	Option<nstd :: U_int32_t> :: Option
	(
		const Type_ defaultValue,
		const char* cmdString,
		const char* usageMessage,
		const char  cmdChar,
		const int   largeIndent
	) :
	value_ (defaultValue),
	name_ (cmdString),
	option_ (INITIAL_OPTION_CAPACITY),
	defaultValue_ (defaultValue),
	cmdString_ (cmdString),
	usageMessage_ (usageMessage),
	cmdChar_ (cmdChar),
	largeIndent_ (largeIndent),
	isNameless_ (false),
	sscanfParam_ ("%d"),
	typeName_ ("<int>"),
	isScaned_ (false),
	isCorrect_ (true) {
	}
	template<>
	inline
	Option<nstd :: Int32_t> :: Option
	(
		const Type_ defaultValue,
		const char* cmdString,
		const char* usageMessage,
		const char  cmdChar,
		const int   largeIndent
	) :
	value_ (defaultValue),
	name_ (cmdString),
	option_ (INITIAL_OPTION_CAPACITY),
	defaultValue_ (defaultValue),
	cmdString_ (cmdString),
	usageMessage_ (usageMessage),
	cmdChar_ (cmdChar),
	largeIndent_ (largeIndent),
	isNameless_ (false),
	sscanfParam_ ("%d"),
	typeName_ ("<int>"),
	isScaned_ (false),
	isCorrect_ (true) {
	}
	template<>
	inline
	Option<nstd :: U_int16_t> :: Option
	(
		const Type_ defaultValue,
		const char* cmdString,
		const char* usageMessage,
		const char  cmdChar,
		const int   largeIndent
	) :
	value_ (defaultValue),
	name_ (cmdString),
	option_ (INITIAL_OPTION_CAPACITY),
	defaultValue_ (defaultValue),
	cmdString_ (cmdString),
	usageMessage_ (usageMessage),
	cmdChar_ (cmdChar),
	largeIndent_ (largeIndent),
	isNameless_ (false),
	sscanfParam_ ("%d"),
	typeName_ ("<int>"),
	isScaned_ (false),
	isCorrect_ (true) {
	}
	template<>
	inline
	Option<nstd :: Int16_t> :: Option
	(
		const Type_ defaultValue,
		const char* cmdString,
		const char* usageMessage,
		const char  cmdChar,
		const int   largeIndent
	) :
	value_ (defaultValue),
	name_ (cmdString),
	option_ (INITIAL_OPTION_CAPACITY),
	defaultValue_ (defaultValue),
	cmdString_ (cmdString),
	usageMessage_ (usageMessage),
	cmdChar_ (cmdChar),
	largeIndent_ (largeIndent),
	isNameless_ (false),
	sscanfParam_ ("%d"),
	typeName_ ("<int>"),
	isScaned_ (false),
	isCorrect_ (true) {
	}
	template<>
	inline
	Option<bool> :: Option
	(
		const Type_ defaultValue,
		const char* cmdString,
		const char* usageMessage,
		const char  cmdChar,
		const int   largeIndent
	) :
	value_ (defaultValue),
	name_ (cmdString),
	option_ (INITIAL_OPTION_CAPACITY),
	defaultValue_ (defaultValue),
	cmdString_ (cmdString),
	usageMessage_ (usageMessage),
	cmdChar_ (cmdChar),
	largeIndent_ (largeIndent),
	isNameless_ (false),
	sscanfParam_ (""),
	typeName_ (""),
	isScaned_ (false),
	isCorrect_ (true) {
	}
	template<>
	inline
	Option<nstd :: String<> > :: Option() :
	value_ (INITIAL_STRING_CAPACITY),
	name_ (INITIAL_NAME_CAPACITY),
	option_ (INITIAL_OPTION_CAPACITY),
	defaultValue_ (INITIAL_STRING_CAPACITY),
	cmdString_ ("option-string"),
	usageMessage_ (""),
	cmdChar_ (chars :: NULL_CHAR),
	largeIndent_ (DEFAULT_LARGE_INDENT),
	isNameless_ (true),
	sscanfParam_ (""),
	typeName_ ("<string>"),
	isScaned_ (false),
	isCorrect_ (true) {
	}
	template<>
	inline
	Option<nstd :: String<> > :: Option
	(
		const Type_ defaultValue,
		const char* cmdString,
		const char* usageMessage,
		const char  cmdChar,
		const int   largeIndent
	) :
	value_ (defaultValue),
	name_ (cmdString),
	option_ (defaultValue),
	defaultValue_ (defaultValue),
	cmdString_ (cmdString),
	usageMessage_ (usageMessage),
	cmdChar_ (cmdChar),
	largeIndent_ (largeIndent),
	isNameless_ (false),
	sscanfParam_ (""),
	typeName_ ("<string>"),
	isScaned_ (false),
	isCorrect_ (true) {
	}
	template<>
	inline
	Option<nstd :: Path<> > :: Option() :
	value_ (),
	name_ (INITIAL_NAME_CAPACITY),
	option_ (INITIAL_OPTION_CAPACITY),
	defaultValue_ (),
	cmdString_ ("option-path"),
	usageMessage_ (""),
	cmdChar_ (chars :: NULL_CHAR),
	largeIndent_ (DEFAULT_LARGE_INDENT),
	isNameless_ (true),
	sscanfParam_ (""),
	typeName_ ("<path>"),
	isScaned_ (false),
	isCorrect_ (true) {
	}
	template<>
	inline
	Option<nstd :: Path<> > :: Option
	(
		const Type_ defaultValue,
		const char* cmdString,
		const char* usageMessage,
		const char  cmdChar,
		const int   largeIndent
	) :
	value_ (defaultValue),
	name_ (cmdString),
	option_ (defaultValue.getString()),
	defaultValue_ (defaultValue),
	cmdString_ (cmdString),
	usageMessage_ (usageMessage),
	cmdChar_ (cmdChar),
	largeIndent_ (largeIndent),
	isNameless_ (false),
	sscanfParam_ (""),
	typeName_ ("<path>"),
	isScaned_ (false),
	isCorrect_ (true) {
	}
	template<class T>
	inline
	Option<T> :: ~ Option() {
	}

	template<class T>
	inline typename Option<T> :: Type_&
	Option<T> :: value() {
		return value_;
	}
	template<class T>
	inline typename Option<T> :: String_&
	Option<T> :: name() {
		return name_;
	}
	template<class T>
	inline const typename Option<T> :: Type_&
	Option<T> :: getValue() const {
		return value_;
	}

	template<class T>
	inline bool
	Option<T> :: isScaned() const {
		return isScaned_;
	}
	template<class T>
	inline bool
	Option<T> :: isCorrect() const {
		return isCorrect_;
	}
	template<class T>
	bool
	Option<T> :: isDefault() const {
		return (value_ == defaultValue_);
	}

	template<class T>
	inline const char*
	Option<T> :: getName() const {
		return name_.c_str();
	}
	template<class T>
	inline const char*
	Option<T> :: getString() const {
		return cmdString_;
	}
	template<class T>
	inline const char*
	Option<T> :: getUsageMessage() const {
		return usageMessage_;
	}

	template<class T>
	bool
	Option<T> :: proceedStringOption (const char* opt, const int argCount, const char* argValues[], int& i)
	{
		if (Base :: equalStrings (opt, cmdString_)) {
			if (isNameless_) {
				name_.copyFrom (argValues [++ i]);
			}
			++ i;
			isCorrect_ = (sscanf (argValues [i], sscanfParam_, &value_) > 0);
			option_.copyFrom (argValues [i]);
			if (!isCorrect_) {
				std :: cout << "incorrect option format: " << option_ << std :: endl;
			}
			isScaned_ = true;
			return true;
		} else {
			return false;
		}
	}
	template<>
	bool
	Option<bool> :: proceedStringOption (const char* opt, const int argCount, const char* argValues[], int& i)
	{
		if (Base :: equalStrings (opt, cmdString_)) {
			if (isNameless_) {
				name_.copyFrom (argValues [++ i]);
			}
			option_.copyFrom (argValues [i]);
			isScaned_ = true;
			if (i + 1 < argCount) {
				const char* next = argValues [i + 1];
				if (Base :: equalStrings (next, "on")) {
					++ i;
					value_ = true;
				} else if (Base :: equalStrings (next, "true")) {
					++ i;
					value_ = true;
				} else if (Base :: equalStrings (next, "yes")) {
					++ i;
					value_ = true;
				} else if (Base :: equalStrings (next, "off")) {
					++ i;
					value_ = false;
				} else if (Base :: equalStrings (next, "false")) {
					++ i;
					value_ = false;
				} else if (Base :: equalStrings (next, "no")) {
					++ i;
					value_ = false;
				} else {
					value_ = true;
				}
			} else {
				value_ = true;
			}
			return true;
		} else {
			return false;
		}
	}
	template<>
	bool
	Option<nstd :: String<> > :: proceedStringOption (const char* opt, const int argCount, const char* argValues[], int& i)
	{
		if (Base :: equalStrings (opt, cmdString_)) {
			if (isNameless_) {
				name_.copyFrom (argValues [++ i]);
			}
			isScaned_ = true;
			++ i;
			value_.copyFrom (argValues [i]);
			option_.copyFrom (argValues [i]);
			return true;
		} else {
			return false;
		}
	}
	template<>
	bool
	Option<nstd :: Path<> > :: proceedStringOption (const char* opt, const int argCount, const char* argValues[], int& i)
	{
		if (Base :: equalStrings (opt, cmdString_)) {
			if (isNameless_) {
				name_.copyFrom (argValues [++ i]);
			}
			isScaned_ = true;
			++ i;
			const char* path = argValues [i];
			value_.parse(path);
			option_.copyFrom (path);
			return true;
		} else {
			return false;
		}
	}

	template<class T>
	bool
	Option<T> :: proceedOneCharOption (const char* opt, const int argCount, const char* argValues[], int& i)
	{
		if (cmdChar_ == chars :: NULL_CHAR) {
			return false;
		}
		if (*opt == cmdChar_) {
			++ i;
			isCorrect_ = (sscanf (argValues [i], sscanfParam_, &value_) > 0);
			option_.copyFrom (argValues [i]);
			if (!isCorrect_) {
				std :: cout << "incorrect option format: " << option_ << std :: endl;
			}
			isScaned_ = true;
			return true;
		}
		return false;
	}
	template<>
	bool
	Option<bool> :: proceedOneCharOption (const char* opt, const int argCount, const char* argValues[], int& i)
	{
		if (*opt == cmdChar_) {
			option_.copyFrom (argValues [i]);
			isScaned_ = true;
			if (i + 1 < argCount) {
				const char* next = argValues [i + 1];
				if (Base :: equalStrings (next, "on")) {
					++ i;
					value_ = true;
				} else if (Base :: equalStrings (next, "true")) {
					++ i;
					value_ = true;
				} else if (Base :: equalStrings (next, "yes")) {
					++ i;
					value_ = true;
				} else if (Base :: equalStrings (next, "off")) {
					++ i;
					value_ = false;
				} else if (Base :: equalStrings (next, "false")) {
					++ i;
					value_ = false;
				} else if (Base :: equalStrings (next, "no")) {
					++ i;
					value_ = false;
				} else {
					value_ = true;
				}
			} else {
				value_ = true;
			}
			return true;
		}
		return false;
	}
	template<>
	bool
	Option<nstd :: String<> > :: proceedOneCharOption (const char* opt, const int argCount, const char* argValues[], int& i)
	{
		if (cmdChar_ == chars :: NULL_CHAR) {
			return false;
		}
		if (*opt == cmdChar_) {
			++ i;
			value_.copyFrom (argValues [i]);
			option_.copyFrom (argValues [i]);
			return true;
		}
		return false;
	}
	template<>
	bool
	Option<nstd :: Path<> > :: proceedOneCharOption (const char* opt, const int argCount, const char* argValues[], int& i)
	{
		if (cmdChar_ == chars :: NULL_CHAR) {
			return false;
		}
		if (*opt == cmdChar_) {
			++ i;
			const char* path = argValues [i];
			value_.parse(path);
			option_.copyFrom (path);
			isScaned_ = true;
			isCorrect_ = true;
			/*isCorrect_ = value_.isCorrect();
			if (!isCorrect_) {
				std :: cout << "incorrect path format: " << option_ << std :: endl;
			}*/
			return true;
		}
		return false;
	}

	template<class T>
	template<class S>
	void
	Option<T> :: showUsageMessage (S& os) const
	{
		showMainUsageMessage (os);
		showDefaultUsageMessage (os);
		os << chars :: NEW_LINE;
	}
	template<class T>
	template<class S>
	void
	Option<T> :: showOptionValues (S& os) const
	{
		showMainOptionValues(os);
		showDefaultOptionValues(os);
		os << chars :: NEW_LINE;
	}

	template<class T>
	void
	Option<T> :: commitSuicide() {
		delete this;
	}
	template<class T>
	inline Size_t
	Option<T> :: getVolume() const
	{
		Size_t volume = 0;
		volume += name_.getVolume();
		volume += option_.getVolume();
		return volume;
	}
	template<>
	inline Size_t
	Option<nstd :: String<> > :: getVolume() const
	{
		Size_t volume = 0;
		volume += value_.getVolume();
		volume += name_.getVolume();
		volume += option_.getVolume();
		volume += defaultValue_.getVolume();
		return volume;
	}
	template<>
	inline Size_t
	Option<nstd :: Path<> > :: getVolume() const
	{
		Size_t volume = 0;
		volume += value_.getVolume();
		volume += name_.getVolume();
		volume += option_.getVolume();
		volume += defaultValue_.getVolume();
		return volume;
	}
	template<class T>
	inline Size_t
	Option<T> :: getSizeOf() const {
		return sizeof (Option);
	}
	template<class T>
	template<class S>
	void
	Option<T> :: show (S& string) const
	{
		if (isNameless_ && (name_.getSize() > LONG_OPTION_SIZE)) {
			string << "--" << cmdString_ << chars :: NEW_LINE;
			if (isNameless_) {
				string << chars :: TAB << name_ << chars :: NEW_LINE;
			}
			string << chars :: TAB << value_ << chars :: NEW_LINE;
		} else {
			string << "--" << cmdString_ << chars :: SPACE;
			if (isNameless_) {
				string << name_ << chars :: SPACE;
			}
			string << value_ << chars :: SPACE;
		}
	}
	template<>
	template<class S>
	void
	Option<nstd :: String<> > :: show (S& string) const
	{
		const bool longOption =
			isNameless_ ?
			(
				(name_.getSize() > LONG_OPTION_SIZE) ||
				(value_.getSize() > LONG_OPTION_SIZE)
			) :
			(value_.getSize() > LONG_OPTION_SIZE);

		if (longOption) {
			string << "--" << cmdString_ << chars :: NEW_LINE;
			if (isNameless_) {
				string << chars :: TAB << name_ << chars :: NEW_LINE;
			}
			string << chars :: TAB << value_ << chars :: NEW_LINE;
		} else {
			string << "--" << cmdString_ << chars :: SPACE;
			if (isNameless_) {
				string << name_ << chars :: SPACE;
			}
			string << value_ << chars :: SPACE;
		}
	}

	/****************************
	 *		Private members
	 ****************************/

	template<class T>
	template<class S>
	void
	Option<T> :: showMainUsageMessage (S& os) const
	{
		if (cmdChar_ == chars :: NULL_CHAR) {
			for (int i = 0; i < DEFAULT_SMALL_INDENT; ++ i) {
				os << " ";
			}
		} else {
			os << "  -" << cmdChar_ << ",  ";
		}
		os << "--" << cmdString_ << " " << typeName_;
		const int cmdLength = Base :: stringLength (cmdString_);
		const int tpNameLength = Base :: stringLength (typeName_);
		const int delta = DEFAULT_LARGE_INDENT - (DEFAULT_SMALL_INDENT + cmdLength + tpNameLength + 3);
		if (delta > 0) {
			for (int i = 0; i < delta; ++ i) {
				os << " ";
			}
		} else {
			os << " ";
		}
		os << usageMessage_ << " ";
	}
	template<class T>
	template<class S>
	void
	Option<T> :: showMainOptionValues (S& os) const
	{
		if (General :: showConfigDefaults() || !isDefault()) {
			os << "\tvalue: " << cmdString_ << " = " << value_;
		}
	}
	template<>
	template<class S>
	void
	Option<bool> :: showMainOptionValues (S& os) const
	{
		if (General :: showConfigDefaults() || !isDefault()) {
			os << "\tvalue: " << cmdString_ << " = " << (value_ ? "true" : "false");
		}
	}
	template<class T>
	template<class S>
	void
	Option<T> :: showDefaultUsageMessage (S& os) const
	{
		if (defaultValue_ != Undefined<Type_> :: getValue()) {
			os << "By default = " << defaultValue_;
		}
	}
	template<>
	template<class S>
	void
	Option<nstd :: Path<> > :: showDefaultUsageMessage (S& os) const
	{
		if (!defaultValue_.isUndefined()) {
			os << "By default = " << defaultValue_;
		}
	}
	template<class T>
	template<class S>
	void
	Option<T> :: showDefaultOptionValues (S& os) const
	{
		if (General :: showConfigDefaults() && isDefault()) {
			os << " (default)";
		}
	}
}
}
}

#endif /*NSTD_CONFIG_OPTION_OPTION_CPP_*/
