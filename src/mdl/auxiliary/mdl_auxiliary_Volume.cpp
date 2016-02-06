/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       engine_auxiliary_Volume.cpp                                 */
/* Description:     class for program data volume counters                   */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "mdl/mdl_Engine.hpp"

namespace mdl {
namespace auxiliary {

	/****************************
	 *		Public members
	 ****************************/

	template<class S>
	void
	Volume :: show
	(
		S& string,
		bool volume,
		bool balance,
		bool difference,
		bool calculate
	)
	{
		if (calculate) {
			previous_ = current_;
			current_  = calculateVolume();
		}
		const bool doShowVolume  = Config :: showVolume() || volume;
		const bool doShowBalance = Config :: showMemoryBalance() || balance || (current_.delta_ != 0);
		if (!doShowVolume && !doShowBalance && !difference) {
			return;
		}
		string << chars :: NEW_LINE;
		if (doShowVolume) {
			showVolume (string, current_, "memory usage summary:");
		}
		if (difference) {
			showVolume (string, current_ - previous_, "difference with previous:");
		}
		if (doShowBalance) {
			showBalance (string, current_);
		}
	}
	Size_t
	Volume :: getBalance()
	{
		previous_ = current_;
		current_  = calculateVolume();
		return current_.delta_;
	}

	/****************************
	 *		Private members
	 ****************************/

	Volume :: Data_
	Volume :: Data_ :: operator - (Data_ operand)
	{
		Data_ data;
		data.names_  = names_  - operand.names_;
		data.math_   = math_   - operand.math_;
		data.prover_ = prover_ - operand.prover_;
		data.source_ = source_ - operand.source_;

		data.object_  = object_ - operand.object_;
		data.memory_  = memory_ - operand.memory_;
		data.config_  = config_ - operand.config_;
		data.lexer_   = lexer_  - operand.lexer_;
		data.server_  = server_ - operand.server_;
		data.console_ = console_ - operand.console_;
		data.parser_  = parser_ - operand.parser_;
		data.refactor_= parser_ - operand.refactor_;
		data.engine_  = engine_ - operand.engine_;

		data.used_      = used_      - operand.used_;
		data.allocated_ = allocated_ - operand.allocated_;
		data.delta_     = delta_     - operand.delta_;
		return data;
	}
	inline void
	Volume :: Data_ :: calculateUsed()
	{
		used_ =
			source_ + names_  + math_   + prover_ + object_ + memory_ +
			config_ + lexer_  + server_ + console_+ parser_ + refactor_ + engine_;
	}
	template<class S>
	inline void
	Volume :: Data_ :: show (S& string, Ptrdiff_t value, const char* name)
	{
		if (value != 0) {
			string << memory :: UsageMessage (used_, value, name) << chars :: NEW_LINE;
		}
	}

	Volume :: Data_
	Volume :: calculateVolume()
	{
		Data_ data;
		data.names_  = Table  :: getVolume();
		data.math_   = Math   :: getVolume();
		data.prover_ = (Prover :: get() == NULL) ? 0 : Prover :: get()->getVolume();
		data.source_ = (Source :: get() == NULL) ? 0 : Source :: get()->getVolume();

		data.object_  = object  :: Object :: getStringVolume();
		data.memory_  = Memory  :: getUsedVolume();
		data.config_  = Config  :: getVolume();
		data.lexer_   = lexer   :: Location :: getPositionListVolume();
		data.server_  = (Server  :: get() == NULL) ? 0 : Server :: get()->getVolume();
		data.console_ = (Console :: get() == NULL) ? 0 : Console :: get()->getVolume();
		data.parser_  = (Parser  :: get() == NULL) ? 0 : Parser :: get()->getVolume();
		data.engine_  = (Engine  :: get() == NULL) ? 0 : Engine :: get()->getVolume();
		data.refactor_ = (Refactorer  :: get() == NULL) ? 0 : Refactorer :: get()->getVolume();

		data.calculateUsed();

		data.allocated_ = Memory :: getAllocatedVolume();
		data.delta_     = data.allocated_ - data.used_;
		return data;
	}
	template<class S>
	void
	Volume :: showVolume (S& string, Data_ data, const char* header)
	{
		string << header << chars :: NEW_LINE;
		string << "---------------------------" << chars :: NEW_LINE;
		data.show (string, data.used_,     "total    volume");
		data.show (string, data.math_,     "math     volume");
		data.show (string, data.names_,    "names    volume");
		data.show (string, data.source_,   "source   volume");
		data.show (string, data.prover_,   "prover   volume");
		data.show (string, data.engine_,   "engine   volume");
		data.show (string, data.server_,   "server   volume");
		data.show (string, data.console_,  "console  volume");
		data.show (string, data.parser_,   "parser   volume");
		data.show (string, data.config_,   "config   volume");
		data.show (string, data.memory_,   "memory   volume");
		data.show (string, data.object_,   "object   volume");
		data.show (string, data.refactor_, "refactor volume");
		string << chars :: NEW_LINE;
	}
	template<class S>
	void
	Volume :: showBalance (S& string, Data_ data)
	{
		string << "memory balance (must be 0):" << chars :: NEW_LINE;
		string << "-------------------------------" << chars :: NEW_LINE;
		string << "delta:\t" << data.delta_ << " bytes = ";
		string << data.allocated_ << " (allocated) - " << data.used_ << " (used) = ";
		memory :: Unit :: show (string, data.delta_);
		string << chars :: NEW_LINE;
		string << chars :: NEW_LINE;
	}

	/*********************************
	 *		Private static members
	 *********************************/

	Volume :: Data_ Volume :: current_;
	Volume :: Data_ Volume :: previous_;
}
}


