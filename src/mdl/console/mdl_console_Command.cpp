/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_console_Command.cpp                                  */
/* Description:     mdl console command                                      */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_CONSOLE_COMMAND_CPP_
#define MDL_CONSOLE_COMMAND_CPP_

namespace mdl {
namespace console {

	/****************************
	 *		Public members
	 ****************************/

	Command :: Command(const char* text) :
	text_ (text),
	id_ (NONE),
	isSane_ (false),
	arguments_ ()
	{
		if (message_ == NULL) {
			message_ = new String (INITIAL_MESSAGE_CAPACITY);
			owner_   = this;
		}
	}
	Command :: Command(const String& text) :
	text_ (text),
	id_ (NONE),
	isSane_ (false),
	arguments_ ()
	{
		if (message_ == NULL) {
			message_ = new String (INITIAL_MESSAGE_CAPACITY);
			owner_   = this;
		}
	}
	Command :: ~ Command()
	{
		if (this == owner_) {
			deleteAggregateObject (message_);
			owner_ = NULL;
		}
	}

	void
	Command :: parse (Engine* engine)
	{
		const char* c = text_.c_str();
		const char* beg = skipWhitespace (c);
		const char* end = readToken (c);
		String name (beg, end);
		parseName (name);
		while (*c != chars :: NULL_CHAR) {
			const char* beg = skipWhitespace (c);
			const char* end = readToken (c);
			String* argument = new String (beg, end);
			arguments_.add (argument);
		}
		checkSanity (engine);
	}
	void
	Command :: execute (Engine* engine)
	{
		switch (id_) {
		case SHOW   : //< intentionally
		case HELP   : //< intentionally
		case LIST   : executeAuxiliary (engine); break;
		case EXIT   : break;

		case READ   : engine->read();   break;
		case CHECK  : engine->check();  break;
		case PROVE  : engine->prove();  break;
		case WRITE  : engine->write();  break;
		case SETUP  : updateConfig();   break;
		case TRANSLATE : engine->translate(); break;
		case LEARN  : engine->learn();  break;
		case LOOKUP : engine->lookup(); break;
		case MINE   : engine->mine();   break;

		case PLANT_TREE : engine->plantTree(); break;
		case GROW_TREE  : engine->growTree();  break;
		case CONFIRM    : engine->confirmProof(); break;
		case FELL_TREE  : engine->fellTree(); break;
		case INFO_TREE  : engine->infoTree(); break;

		case NONE   : break;
		default     : break;
		}
		if (Volume :: getBalance() != 0) {
			String& message = getMessage();
			Volume :: show (message, false, true, false, false);
			showMessage (message);
		}
	}

using manipulator :: endLine;
using manipulator :: space;
using manipulator :: tab;

	// object :: Object implementation
	void
	Command :: commitSuicide() {
		delete this;
	}
	Size_t
	Command :: getVolume() const
	{
		Size_t volume = 0;
		volume += text_.getVolume();
		volume += arguments_.getVolume();
		if (this == owner_) {
			volume += getAggregateVolume (message_);
		}
		return volume;
	}
	Size_t
	Command :: getSizeOf() const {
		return sizeof (Command);
	}
	void
	Command :: show (String& string) const
	{
		showId (string);
		string << chars :: SPACE;
		for (int i = 0; i < arguments_.getSize(); ++ i) {
			const String* argument = arguments_.getValue(i);
			string << *argument << chars :: SPACE;
		}
	}

	/****************************
	 *		Private members
	 ****************************/

	void
	Command :: parseName(const String& name)
	{
		id_ = NONE;
		switch (*name.getFirstChar()) {
		case 's' : {
			if (name == "show")   { id_ = SHOW; } else
			if (name == "setup")  { id_ = SETUP; }
			break;
		}
		case 'h' : if (name == "help")   { id_ = HELP; }   break;
		case 'l' : {
			if (name == "list")   { id_ = LIST;   } else
			if (name == "learn")  { id_ = LEARN;  } else
			if (name == "lookup") { id_ = LOOKUP; }
			break;
		}
		case 'e' : if (name == "exit")   { id_ = EXIT; }   break;
		case 'r' : if (name == "read")   { id_ = READ; }   break;
		case 'c' : {
			if (name == "check")   { id_ = CHECK; } else
			if (name == "confirm") { id_ = CONFIRM; }
			break;
		}
		case 'p' :  {
			if (name == "prove") { id_ = PROVE; } else
			if (name == "plant") { id_ = PLANT_TREE; }
			break;
		}
		case 'w' : if (name == "write")  { id_ = WRITE; }  break;
		case 't' : if (name == "translate") { id_ = TRANSLATE; } break;
		case 'm' : if (name == "mine")   { id_ = MINE; }      break;
		case 'g' : if (name == "grow")   { id_ = GROW_TREE; } break;
		case 'f' : if (name == "fell")   { id_ = FELL_TREE; } break;
		case 'i' : if (name == "info")   { id_ = INFO_TREE; } break;
		default : break;
		}
	}
	const char*
	Command :: skipWhitespace (const char*& c) const {
		while (true) {
			const char ch = *c;
			if ((ch > chars :: SPACE) || (ch == chars :: NULL_CHAR)) {
				break;
			}
			++c;
		}
		return c;
	}
	const char*
	Command :: readToken (const char*& c) const {
		while (true) {
			const char ch = *c;
			if ((ch <= chars :: SPACE) || (ch == chars :: NULL_CHAR)) {
				break;
			}
			++c;
		}
		return c;
	}

	void
	Command :: updateConfig()
	{
		const int argc = arguments_.getSize();
		const char* argv [argc];
		for (int i = 0; i < argc; ++ i) {
			argv[i] = arguments_.getValue(i)->c_str();
		}
		Config :: proceed (argc, argv);
		Config :: analyseArguments();
	}

	void
	Command :: checkSanity (Engine* engine)
	{
		isSane_ = true;
		switch (id_) {
		case NONE   : checkNoneSanity (engine); break;
		case SHOW   : checkShowSanity (engine); break;
		case HELP   : checkHelpSanity (engine); break;
		case LIST   : checkListSanity (engine); break;
		case EXIT   : checkExitSanity (engine); break;

		case READ      : checkSanity (engine, MUST_NOT_HAVE_ARGS | MUST_HAVE_INPUT_PATH);    break;
		case CHECK     : checkSanity (engine, MUST_NOT_HAVE_ARGS | MUST_HAVE_PARSED_SOURCE); break;
		case PROVE     : checkSanity (engine, MUST_NOT_HAVE_ARGS | MUST_HAVE_PARSED_SOURCE); break;
		case WRITE     : checkSanity (engine, MUST_NOT_HAVE_ARGS | MUST_HAVE_OUTPUT_PATH);   break;
		case SETUP     : checkSanity (engine, MUST_HAVE_ARGS); break;
		case TRANSLATE : checkSanity (engine, MUST_NOT_HAVE_ARGS | MUST_HAVE_PARSED_SOURCE | MUST_HAVE_OUTPUT_PATH); break;
		case LEARN     : checkSanity (engine, MUST_NOT_HAVE_ARGS | MUST_HAVE_PARSED_SOURCE); break;
		case LOOKUP    : checkSanity (engine, MUST_NOT_HAVE_ARGS | MUST_HAVE_PARSED_SOURCE); break;
		case MINE      : checkSanity (engine, MUST_NOT_HAVE_ARGS | MUST_HAVE_PARSED_SOURCE); break;

		case PLANT_TREE: checkSanity (engine, MUST_NOT_HAVE_ARGS | MUST_HAVE_PARSED_SOURCE | MUST_NOT_HAVE_PROVER_TREE); break;
		case GROW_TREE : checkSanity (engine, MUST_NOT_HAVE_ARGS | MUST_HAVE_PARSED_SOURCE | MUST_HAVE_PROVER_TREE); break;
		case CONFIRM   : checkSanity (engine, MUST_NOT_HAVE_ARGS | MUST_HAVE_PARSED_SOURCE | MUST_HAVE_PROVER_TREE); break;
		case FELL_TREE : checkSanity (engine, MUST_NOT_HAVE_ARGS | MUST_HAVE_PARSED_SOURCE); break;
		case INFO_TREE : checkSanity (engine, MUST_NOT_HAVE_ARGS | MUST_HAVE_PARSED_SOURCE | MUST_HAVE_PROVER_TREE); break;
		default        : isSane_ = false; break;
		}
	}

	inline void
	Command :: checkListSanity (Engine* engine) {
		checkSanity (engine, MUST_NOT_HAVE_ARGS);
	}
	void
	Command :: checkShowSanity (Engine* engine)
	{
		checkSanity (engine, MUST_HAVE_ARGS);
		if (isSane_) {
			if (showMode() == SHOW_INVALID) {
				isSane_ = false;
				String& message = getMessage();
				message << "second 'show' argument is invalid. ";
				showMessage (message);
			}
			if (arguments_.getSize() == 1) {
				arguments_.add (new String("all"));
			}
		}
	}
	void
	Command :: checkNoneSanity (Engine* engine)
	{
		isSane_ = false;
		String& message = getMessage();
		message << "none valid command is chosen." << endLine;
		message << "Type 'help' to see the list of all available commands." << endLine;
		showMessage (message);
	}
	inline void
	Command :: checkHelpSanity (Engine* engine) {
		isSane_ = true;
	}
	inline void
	Command :: checkExitSanity (Engine* engine) {
		checkSanity (engine, MUST_NOT_HAVE_ARGS);
	}

	void
	Command :: checkSanity (Engine* engine, const char sanityTests)
	{
		String& message = getMessage();;
		if ((sanityTests & MUST_HAVE_ARGS) && (arguments_.getSize() == 0)) {
			message << "command '";	showId (message); message << "' must have arguments." << endLine;
			isSane_ = false;
		}
		if ((sanityTests & MUST_NOT_HAVE_ARGS) && (arguments_.getSize() > 0)) {
			message << "command '";	showId (message); message << "' must not have arguments." << endLine;
			isSane_ = false;
		}
		if ((sanityTests & MUST_HAVE_PARSED_SOURCE) && (Source :: get() == NULL)) {
			message << "command '";	showId (message); message << "' presumes source already parsed." << endLine;
			isSane_ = false;
		}
		if ((sanityTests & MUST_HAVE_INPUT_PATH) && (Config :: getSource().isUndefined())) {
			message << "command '";	showId (message); message << "' presumes source path defined." << endLine;
			isSane_ = false;
		}
		if ((sanityTests & MUST_HAVE_OUTPUT_PATH) && (Config :: getTarget().isUndefined())) {
			message << "command '";	showId (message); message << "' presumes target path defined." << endLine;
			isSane_ = false;
		}
		if ((sanityTests & MUST_HAVE_PROVER_TREE) && (Tree :: get() == NULL)) {
			message << "command '";	showId (message); message << "' presumes prover tree already build." << endLine;
			isSane_ = false;
		}
		if ((sanityTests & MUST_NOT_HAVE_PROVER_TREE) && (Tree :: get() != NULL)) {
			message << "command '";	showId (message); message << "' presumes that there is no proof tree." << endLine;
			isSane_ = false;
		}
		showMessage (message);
	}

	Command :: ShowMode_
	Command :: showMode() const
	{
		ShowMode_ result = SHOW_INVALID;
		const String& mode = *arguments_[0];
		switch (*mode.getFirstChar()) {
		case 'o' :
			if (mode == "options") { result = SHOW_OPTIONS; } break;
		case 'v' :
			if (mode == "values")  { result = SHOW_VALUES; } else
			if (mode == "volume")  { result = SHOW_VOLUME; } break;
		case 'm' :
			if (mode == "memory")  { result = SHOW_MEMORY; } else
			if (mode == "math")    { result = SHOW_MATH; } break;
		case 't' :
			if (mode == "timing")  { result = SHOW_TIMING; } break;
		default : break;
		}
		return result;
	}
	void
	Command :: executeAuxiliary (Engine* engine) const
	{
		String& message = getMessage();
		switch (id_) {
		case SHOW   : show (message, engine); break;
		case HELP   : help (message);    break;
		case LIST   : list (message);    break;
		default   : break;
		}
		showMessage (message);
	}

	void
	Command :: help (String& string) const
	{
		if ((arguments_.getSize() == 1) && (*arguments_[0] == "mdl")) {
			Config :: showUsageMessage (string);
		} else {
			string << "mdl console commands:" << chars :: NEW_LINE;
			string << "---------------------" << chars :: NEW_LINE;
			string << "         [Auxiliary]" << chars :: NEW_LINE;
			string << "  help                 prints this list" << chars :: NEW_LINE;
			string << "  help mdl             prints the help on the mdl options" << chars :: NEW_LINE;
			string << "  list                 lists all categories of options" << chars :: NEW_LINE;
			string << "  show options <list>  shows the options from <list>" << chars :: NEW_LINE;
			string << "  show values  <list>  shows the option values from <list>" << chars :: NEW_LINE;
			string << "  setup <options>      sets up options, see 'show options'" << chars :: NEW_LINE;
			string << chars :: NEW_LINE;
			string << "  show memory          shows memory allocation info" << chars :: NEW_LINE;
			string << "  show volume          shows memory usage info" << chars :: NEW_LINE;
			string << "  show timing          shows timings of executed commands" << chars :: NEW_LINE;
			string << "  show math            shows source syntax tree statistics" << chars :: NEW_LINE;
			string << chars :: NEW_LINE;
			string << "         [Main actions]" << chars :: NEW_LINE;
			string << "  read          read input file" << chars :: NEW_LINE;
			string << "  check         verify proofs" << chars :: NEW_LINE;
			string << "  prove         start prover" << chars :: NEW_LINE;
			string << "  translate     translate source to smm" << chars :: NEW_LINE;
			string << "  learn         start learning algorithm" << chars :: NEW_LINE;
			string << "  lookup        lookup symbols in the source" << chars :: NEW_LINE;
			string << "  mine          mine source for various lists of symbols" << chars :: NEW_LINE;
			string << "  write         write proven theorems to the output" << chars :: NEW_LINE;
			string << chars :: NEW_LINE;
			string << "         [Interactive proving]" << chars :: NEW_LINE;
			string << "  plant tree    plant the proof variant tree" << chars :: NEW_LINE;
			string << "  grow tree     grow up the proof variant tree" << chars :: NEW_LINE;
			string << "  cut tree      destroy the proof variant tree" << chars :: NEW_LINE;
			string << "  info tree     show specific info about tree" << chars :: NEW_LINE;
			string << chars :: NEW_LINE;
			string << "  exit       exit the mdl console or server" << chars :: NEW_LINE;
			string << chars :: NEW_LINE;
		}
	}
	void
	Command :: list (String& string) const {
		Config :: showGroupNames (string);
	}
	void
	Command :: show (String& string, Engine* engine) const
	{
		const int number = arguments_.getSize() - 1;
		const char* arguments [number];
		for (int i = 0; i < number ; ++ i) {
			arguments[i] = arguments_.getValue(i + 1)->c_str();
		}
		ShowMode_ mode = showMode();
		switch (mode) {
		case SHOW_OPTIONS : {
			config :: List groupList (arguments, number);
			Config :: showUsageMessage (string, groupList);
			break;
		}
		case SHOW_VALUES  : {
			config :: List groupList (arguments, number);
			Config :: showOptionValues (string, groupList);
		}
		case SHOW_MEMORY  : {
			Memory :: show (string);
			break;
		}
		case SHOW_VOLUME  : {
			const bool showVolumeOption = Config ::showVolume();
			Config :: infoOption (Config :: SHOW_VOLUME).value() = true;
			Volume :: show (string);
			Config :: infoOption (Config :: SHOW_VOLUME).value() = showVolumeOption;
			break;
		}
		case SHOW_TIMING  :
			engine->getTimers().show (string);
			break;
		case SHOW_MATH :
			Math :: show (string);
			break;
		default : break;
		}
	}
	void
	Command :: showId (String& string) const
	{
		switch (id_) {
		case SHOW   : string << "show";   break;
		case HELP   : string << "help";   break;
		case LIST   : string << "list";   break;
		case EXIT   : string << "exit";   break;

		case READ   : string << "read";   break;
		case CHECK  : string << "check";  break;
		case PROVE  : string << "prove";  break;
		case WRITE  : string << "write";  break;
		case SETUP  : string << "setup";  break;
		case TRANSLATE : string << "translate";  break;
		case LEARN  : string << "learn";  break;
		case LOOKUP : string << "lookup"; break;
		case MINE   : string << "mine";   break;

		case PLANT_TREE : string << "plant";   break;
		case GROW_TREE  : string << "grow";    break;
		case CONFIRM    : string << "confirm"; break;
		case FELL_TREE  : string << "fell";    break;
		case INFO_TREE  : string << "info";    break;

		case NONE   : string << "<unknown: " << text_ << ">"; break;
		default     : string << "<illegal>"; break;
		}
	}

	String&
	Command :: getMessage() const
	{
		message_->clear();
		return *message_;
	}
	void
	Command :: showMessage (String& message) const
	{
		if (Config :: runServer()) {
			Server :: get()->messageBuffer() << message;
		} else {
			std :: cout << message << std :: flush;
		}
	}

	/*********************************
	 *		Static private members
	 *********************************/

	String* Command :: message_ = NULL;
	Command* Command :: owner_  = NULL;
}
}

#endif /*MDL_CONSOLE_COMMAND_CPP_*/
