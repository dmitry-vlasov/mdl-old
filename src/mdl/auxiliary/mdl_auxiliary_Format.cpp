/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_auxiliary_Format.cpp                                 */
/* Description:     the base i/o components terminal reporting               */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

namespace mdl {
namespace auxiliary {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Format :: Format (const value :: Integer depth) :
	up_ (NULL),
	timer_ (),
	depth_ (depth),
	verbosity_ (depth_ + 1),
	down_ (),
	message_ (INITIAL_MESSAGE_CAPACITY),
	formatted_ (INITIAL_MESSAGE_CAPACITY),
	output_ (NULL),
	timeLimit_ (-1),
	hasPrintableSubformat_ (false) {
	}
	inline
	Format :: Format (Format& format, const bool keepVerbosity, const bool keepDepth) :
	up_ (&format),
	timer_ (),
	depth_ (keepDepth ? format.depth_ : format.depth_ + 1),
	verbosity_ (keepVerbosity ? format.verbosity_ : format.verbosity_ + 1),
	down_ (),
	message_ (INITIAL_MESSAGE_CAPACITY),
	formatted_ (INITIAL_MESSAGE_CAPACITY),
	output_ (NULL),
	timeLimit_ (-1),
	hasPrintableSubformat_ (false) {
		up_->down_.add (this);
	}
	Format :: ~ Format()
	{
		if (up_ != NULL) {
			for (int i = 0; i < up_->down_.getSize(); ++ i) {
				const Format* down = up_->down_.getValue (i);
				if (down == this) {
					up_->down_.remove (i);
					break;
				}
			}
		}
	}

	inline value :: Integer
	Format :: getDepth() const {
		return depth_;
	}
	inline value :: Integer
	Format :: getVerbosity() const {
		return verbosity_;
	}
	inline void
	Format :: setVerbosity (const value :: Integer verbosity) {
		verbosity_ = verbosity;
	}
	inline bool
	Format :: isPrintable() const
	{
		return
			(Config :: verbosity() >= verbosity_) &&
			(verbosity_ != Config :: VERBOSE_SILENT);
	}
	inline void
	Format :: setPrintableSubformat (const bool hasPrintableSubformat) {
		hasPrintableSubformat_ = hasPrintableSubformat;
	}
	inline const Timer&
	Format :: getTimer() {
		return timer_;
	}
	inline String&
	Format :: message() {
		return message_;
	}
	inline void
	Format :: setOutput(String& output) {
		output_ = &output;
	}
	inline void
	Format :: unsetOutput() {
		output_ = NULL;
	}

using manipulator :: endLine;
using manipulator :: underline;
using manipulator :: iterate;
using manipulator :: tab;

	void
	Format :: showStart (const Time timeLimit)
	{
		timeLimit_ = timeLimit;
		timer_.start();
		formatted_.clear();
		if (!isPrintable()) {
			message_.clear();
			return;
		}
		makeIndent (formatted_);
		formatted_ << message_;
		if (timeLimit > 0) {
			formatted_ << " (time limit: " << timeLimit << " s)";
		}
		formatted_ << " ... ";
		message_.clear();
		if (hasPrintableSubformat()) {
			formatted_ << endLine;
		}
		outputFormattedMessage();
	}
	void
	Format :: showFinal()
	{
		timer_.stop();
		formatted_.clear();
		if (!isPrintable()) {
			message_.clear();
			return;
		}
		if (hasPrintableSubformat()) {
			makeIndent (formatted_);
		}
		if (!message_.isEmpty()) {
			formatted_ << message_ << " ";
			message_.clear();
		}
		formatted_ << "done in " << timer_;
		if (timeLimit_ > 0) {
			const value :: Real timePassed = timer_.getSeconds();
			const value :: Real deltaTime = timeLimit_ - timePassed;
			formatted_ << " (delta = " << deltaTime << " s.)";
		}
		formatted_ << endLine;
		outputFormattedMessage();
	}
	void
	Format :: showMessage()
	{
		formatted_.clear();
		if (!isPrintable()) {
			message_.clear();
			return;
		}
		makeIndent (formatted_);
		formatted_ << message_ << endLine;
		message_.clear();
		outputFormattedMessage();
	}
	inline void
	Format :: typeIndent (String& string) const {
		makeIndent<String>(string);
	}

	// object :: Object implementation
	void
	Format :: commitSuicide() {
		delete this;
	}
	Size_t
	Format :: getVolume() const
	{
		Size_t volume = 0;
		volume += timer_.getVolume();
		volume += down_.getVolume();
		volume += message_.getVolume();
		volume += formatted_.getVolume();
		return volume;
	}
	Size_t
	Format :: getSizeOf() const {
		return sizeof (Format);
	}
	void
	Format :: show (String& string) const
	{
		string << message_;
		//String* out = output_;
		//const_cast<String*&>(output_) = &string;
		//showMessage();
		//const_cast<String*&>(output_) = out;
	}

	/****************************
	 *		Private members
	 ****************************/

	template<typename S>
	void
	Format :: makeIndent (S& s) const
	{
		for (int i = 0; i < depth_; ++ i) {
			s << chars :: TAB;
		}
	}
	bool
	Format :: hasPrintableSubformat() const
	{
		if (hasPrintableSubformat_) {
			return true;
		}
		for (int i = 0; i < down_.getSize(); ++ i) {
			const Format* down = down_.getValue (i);
			if (down->isPrintable()) {
				return true;
			}
		}
		return false;
	}
	void
	Format :: outputFormattedMessage()
	{
		if (output_ != NULL) {
			*output_ << formatted_;
		} else {
			if (Config :: runServer()) {
				console :: Server ::get()->messageBuffer() << formatted_;
			} else {
				std :: cout << formatted_ << std :: flush;
			}
		}
		formatted_.clear();
	}
}
}


