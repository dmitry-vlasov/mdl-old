/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_config_Paths.cpp                                    */
/* Description:     paths config flags                                       */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "system/nstd_system.hpp"
#include "config/nstd_config_Paths.hpp"

namespace nstd {
namespace config {

	/****************************
	 *		Public members
	 ****************************/

	inline Paths :: Path_&
	Paths :: source() {
		return pathOptions_[SOURCE]->value();
	}
	inline Paths :: Path_&
	Paths :: target() {
		return pathOptions_[TARGET]->value();
	}
	inline Paths :: Path_&
	Paths :: sourceRoot() {
		return pathOptions_[SOURCE_ROOT]->value();
	}
	inline Paths :: Path_&
	Paths :: targetRoot() {
		return pathOptions_[TARGET_ROOT]->value();
	}
	inline Paths :: Path_&
	Paths :: log() {
		return pathOptions_[LOG]->value();
	}
	inline Paths :: PathVector_*
	Paths :: configVector() {
		return configVector_;
	}

	inline const Paths :: Path_&
	Paths :: getSource() {
		return pathOptions_[SOURCE]->getValue();
	}
	inline const Paths :: Path_&
	Paths :: getTarget() {
		return pathOptions_[TARGET]->getValue();
	}
	inline const Paths :: Path_&
	Paths :: getSourceRoot() {
		return pathOptions_[SOURCE_ROOT]->getValue();
	}
	inline const Paths :: Path_&
	Paths :: getTargetRoot() {
		return pathOptions_[TARGET_ROOT]->getValue();
	}
	inline const Paths :: Path_&
	Paths :: getLog() {
		return pathOptions_[LOG]->getValue();
	}
	inline const Paths :: PathVector_*
	Paths :: getConfigVector() {
		return configVector_;
	}

	template<class S>
	void
	Paths :: showUsageMessage (S& os, const List& list)
	{
		if (!list.contains (optionGroupName_)) {
			return;
		}
		os << optionGroupName_ << ':' << chars :: NEW_LINE;
		for (int j = 0; j < OPTION_NUM; ++ j) {
			pathOptions_[j]->showUsageMessage (os);
		}
		os << chars :: NEW_LINE;
	}
	template<class S>
	void
	Paths :: showOptionValues (S& os, const List& list)
	{
		if (list.contains (optionGroupName_)) {
			os << optionGroupName_ << ':' << chars :: NEW_LINE;
			for (int j = 0; j < OPTION_NUM; ++ j) {
				pathOptions_[j]->showOptionValues (os);
			}
			os << chars :: NEW_LINE;
		}
	}
	template<class S>
	inline void
	Paths :: showGroupName (S& os) {
		os << "\t" << optionGroupName_ << chars :: NEW_LINE;
	}

	/****************************
	 *		Protected members
	 ****************************/

using std :: endl;
using std :: cout;

	inline void
	Paths :: init () {
		configVector_ = new PathVector_ (INITIAL_CONFIG_VECTOR_CAPACITY);

		pathOptions_[SOURCE] = new option :: Path ("in",  "the source file", 'i');
		pathOptions_[TARGET] = new option :: Path ("out", "the target file", 'o');
		pathOptions_[SOURCE_ROOT] = new option :: Path ("source-root", "root directory for source");
		pathOptions_[TARGET_ROOT] = new option :: Path ("target-root", "root directory for target");
		pathOptions_[LOG]    = new option :: Path ("log",    "log file location");
		pathOptions_[CONFIG] = new option :: Path ("config", "use specified file to pass parameters");
	}
	void
	Paths :: release ()
	{
		if (configVector_ != NULL) {
			delete configVector_;
			configVector_ = NULL;
		}
		for (int i = 0; i < OPTION_NUM; ++ i) {
			delete pathOptions_ [i];
			pathOptions_ [i] = NULL;
		}
	}
	inline Size_t
	Paths :: getVolume()
	{
		Size_t volume = 0;
		if (configVector_ != NULL) {
			volume += configVector_->getVolume();
			volume += configVector_->getSizeOf();
		}
		for (int i = 0; i < OPTION_NUM; ++ i) {
			volume += Object :: getAggregateVolume (pathOptions_ [i]);
		}
		return volume;
	}

	void
	Paths :: proceedLastOption (const char* path) {
		pathOptions_[SOURCE]->value().parse (path);
	}
	bool
	Paths :: proceedStringOption (const char* opt, const int argCount, const char* argValues[], int& i)
	{
		if (equalStrings (opt, "config")) {
			const char* path = argValues [++ i];
			configVector_->add (new Path_ (path));
			return true;
		}
		for (int j = 0; j < OPTION_NUM; ++ j) {
			if (pathOptions_[j]->proceedStringOption (opt, argCount, argValues, i)) {
				return true;
			}
		}
		return false;
	}
	bool
	Paths :: proceedOneCharOption (const char* opt, const int argCount, const char* argValues[], int& i)
	{
		for (int j = 0; j < OPTION_NUM; ++ j) {
			if (pathOptions_[j]->proceedOneCharOption (opt, argCount, argValues, i)) {
				return true;
			}
		}
		return false;
	}
	bool
	Paths :: checkPaths()
	{
		if (getSource().isDefined() && !checkSource()) {
			return false;
		}
		if (getTarget().isDefined() && !checkTarget()) {
			return false;
		}
		if (getSourceRoot().isDefined() && !checkSourceRoot()) {
			return false;
		}
		if (getTargetRoot().isDefined() && !checkTargetRoot()) {
			return false;
		}
		if (getLog().isDefined() && !checkLog()) {
			return false;
		}
		for (int i = 0; i < configVector_->getSize(); ++ i) {
			const Path_* config = configVector_->getValue (i);
			if (!checkConfig (config)) {
				return false;
			}
		}
		if (getTarget().isDefined() && getSource().isDefined()) {
			if (!checkSourceAndTarget()) {
				return false;
			}
		}
		return true;
	}

	/****************************
	 *		Private members
	 ****************************/

	bool
	Paths :: checkSource()
	{
		if (!getSource().isFile()) {
			cout << "source: " << getSource() << " is not a file." << endl;
			exit_ = true;
			error_ = true;
			return false;
		}
		const Size_t
			sourceSize = system :: getFileSize (getSource().getString().c_str());
		if (sourceSize == 0) {
			cout << "source file: " << getSource() << " is empty." << endl;
			exit_ = true;
			error_ = true;
			return false;
		}
		if (sourceSize == Undefined<Size_t> :: getValue()) {
			cout << "source file: " << getSource() << " is not found." << endl;
			exit_ = true;
			error_ = true;
			return false;
		}
		return true;
	}
	bool
	Paths :: checkTarget()
	{
		if (!getTarget().isFile()) {
			cout << "target: " << getTarget() << " is not a file." << endl;
			exit_ = true;
			error_ = true;
			return false;
		}
		const Size_t
			targetSize = system :: getFileSize (getTarget().getString().c_str());
		if ((targetSize != Undefined<Size_t> :: getValue()) && !General :: overwrite()) {
			cout << "target file: " << getTarget() << " already exists" << endl;
			exit_ = true;
			error_ = true;
			return false;
		}
		return true;
	}
	bool
	Paths :: checkSourceRoot()
	{
		if (!getSourceRoot().isDirectory()) {
			cout << "source root: " << getSourceRoot() << " is not a directory." << endl;
			exit_ = true;
			error_ = true;
			return false;
		}
		if (!system :: directoryExists (getSourceRoot().getString().c_str())) {
			cout << "source root directory: " << getSourceRoot() << " does not exist." << endl;
			exit_ = true;
			error_ = true;
			return false;
		}
		return true;
	}
	bool
	Paths :: checkTargetRoot()
	{
		if (!getTargetRoot().isDirectory()) {
			cout << "target root: " << getTargetRoot() << " is not a directory." << endl;
			exit_ = true;
			error_ = true;
			return false;
		}
		if (!system :: directoryExists (getTargetRoot().getString().c_str())) {
			cout << "target root directory: " << getTargetRoot() << " does not exist." << endl;
			exit_ = true;
			error_ = true;
			return false;
		}
		return true;
	}
	inline bool
	Paths :: checkLog() {
		return true;
	}
	inline bool
	Paths :: checkConfig (const Path_* config)
	{
		if (config == NULL) {
			return true;
		}
		if (!config->isFile()) {
			cout << "config: " << *config << " is not a file." << endl;
			return false;
		}
		const Size_t
			configSize = system :: getFileSize (config->getString().c_str());
		if (configSize == 0) {
			cout << "config file: " << *config << " is empty." << endl;
			return false;
		}
		if (configSize == Undefined<Size_t> :: getValue()) {
			cout << "config file: " << *config << " is not found." << endl;
			return false;
		}
		return true;
	}
	inline bool
	Paths :: checkSourceAndTarget()
	{
		if ((getTarget() == getSource()) && !General :: overwrite()) {
			cout << "source: " << getSource();
			cout <<" and target " << getTarget();
			cout << " files coincide" << endl;
			exit_ = true;
			error_ = true;
			return false;
		}
		return true;
	}

	/************************************
	 *		Static private attributes
	 ************************************/

	Paths :: PathVector_* Paths :: configVector_ = NULL;
	option :: Path* Paths :: pathOptions_ [OPTION_NUM];
	const char* Paths :: optionGroupName_ = "paths";
}
}


