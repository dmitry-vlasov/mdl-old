/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_console_Command.hpp                                  */
/* Description:     mdl console command                                      */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_CONSOLE_COMMAND_HPP_
#define MDL_CONSOLE_COMMAND_HPP_

#include "mdl/console/mdl_console.dpp"

namespace mdl {
namespace console {

class Command :
	public object :: Object,
	public Scalar<Command> {
public :
	enum Id_ {
		// Auxiliary commands
		NONE      = 0,
		HELP      = 1,
		LIST      = 2,
		SHOW      = 3,
		EXIT      = 4,

		// Main action commands
		READ      = 5,
		CHECK     = 6,
		PROVE     = 7,
		WRITE     = 8,
		SETUP     = 9,
		TRANSLATE = 10,
		LEARN     = 11,
		LOOKUP    = 12,
		MINE      = 13,

		// Interactive proving commands
		PLANT_TREE = 14,
		GROW_TREE  = 15,
		CONFIRM    = 16, //< confirm found proof
		FELL_TREE  = 17,
		INFO_TREE  = 18, //< show tree structure

		COMMAND_NUM = 19
	};

	Command (const char* text);
	Command (const String& text);
	virtual ~ Command();

	Id_  getId()  const { return id_; }
	bool isSane() const { return isSane_; }
	void parse (Engine* engine);
	void execute (Engine* engine);

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	friend class Console;
	friend class Server;

	void parseName(const String&);
	const char* skipWhitespace(const char*&) const;
	const char* readToken(const char*&) const;

	void updateConfig();

	void checkSanity (Engine* engine);
	void checkListSanity (Engine* engine);
	void checkShowSanity (Engine* engine);
	void checkNoneSanity (Engine* engine);
	void checkHelpSanity (Engine* engine);
	void checkExitSanity (Engine* engine);
	void checkInfoSanity (Engine* engine);

	enum SanityTests_ {
		MUST_HAVE_ARGS            = 0x01,
		MUST_NOT_HAVE_ARGS        = 0x02,
		MUST_HAVE_PARSED_SOURCE   = 0x04,
		MUST_HAVE_INPUT_PATH      = 0x08,
		MUST_HAVE_OUTPUT_PATH     = 0x10,
		MUST_HAVE_PROVER_TREE     = 0x20,
		MUST_NOT_HAVE_PROVER_TREE = 0x40,
	};

	void checkSanity (Engine* engine, const char sanityTests);

	enum ShowMode_ {
		SHOW_OPTIONS = 0,
		SHOW_VALUES  = 1,
		SHOW_MEMORY  = 2,
		SHOW_VOLUME  = 3,
		SHOW_TIMING  = 4,
		SHOW_MATH    = 5,
		SHOW_INVALID = 6
	};

	ShowMode_ showMode() const;
	void executeAuxiliary (Engine* engine) const;
	void help (String&) const;
	void list (String&) const;
	void show (String&, Engine* engine) const;
	void showId (String&) const;

	enum {
		INITIAL_MESSAGE_CAPACITY = 64
	};

	String& getMessage() const;
	void showMessage (String&) const;

	String text_;
	Id_    id_;
	bool   isSane_;
	vector :: String arguments_;

	static Command* owner_;
	static String* message_;
};

}
}

#endif /*MDL_CONSOLE_COMMAND_HPP_*/
