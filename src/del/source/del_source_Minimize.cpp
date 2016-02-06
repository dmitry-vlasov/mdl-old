/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_source_Minimize.cpp                                  */
/* Description:     question                                                 */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "del/auxiliary/del_auxiliary.hpp"
#include "del/source/del_source.hpp"

namespace del {
namespace source {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Minimize :: Minimize
	(
		const Location& location,
		const del :: Comments* comments,
		const value :: Theory theoryName
	) :
	location_ (location),
	comments_ (comments),
	theoryName_ (theoryName),
	theory_ (Math :: theories()->get (theoryName_)),
	minimalTheory_ (NULL) {
	}
	inline
	Minimize :: Minimize (const del :: Theory* theory) :
	location_ (),
	comments_ (NULL),
	theoryName_ (theory->getName()),
	theory_ (theory),
	minimalTheory_ (NULL) {
	}
	Minimize :: ~ Minimize() {
		deleteAggregateObject (comments_);
	}

using manipulator :: endLine;

	// del :: Minimize implementation
	const del :: Theory*
	Minimize :: getMinimalTheory() const {
		return minimalTheory_;
	}
	const del :: Minimization*
	Minimize :: minimize() const
	{
		const del :: Minimization*
			minimization = NULL;
		Timers :: minimizing().start();
		try {
			Table :: pushVariables();
			//std :: cout << std :: endl << "-----------------------------------" << std :: endl;
			startTheory();
			minimizeTheory();;
			finishTheory();

			minimization = createMinimization();
			//std :: cout << *minimization << std :: endl << std :: endl;
			//std :: cout << std :: endl << "-----------------------------------" << std :: endl;
			//std :: cout << std :: endl << std :: endl << std :: endl << std :: endl;

			Table :: popVariables();
		} catch (exception :: OutOfTime& outOfTime) {
			if (Config :: verbose()) {
				std :: cout << "failed to minimize theory " << Table :: theories()->get (theoryName_) << ": ";
				std :: cout << "out of time." << std :: endl;
			}
		}
		Timers :: minimizing().stop();
		return minimization;
	}

using manipulator :: space;
using manipulator :: underline;
using manipulator :: endLine;

	// object :: Writable implementation
	void
	Minimize :: replicate (String& string) const
	{
		return;
		if (comments_ != NULL) {
			comments_->translate (string);
		}
		string << location_.getIndent();
		string << Token :: minimize_ << space;
		string << Token :: openBracket_;
		string << Table :: theories()->get (theoryName_);
		string << Token :: closeBracket_ << space << endLine;
		string << endLine;
	}
	void
	Minimize :: translate (String& string) const {
		replicate (string);
	}

	// object :: Object implementation
	void
	Minimize :: commitSuicide() {
		delete this;
	}
	Size_t
	Minimize :: getSizeOf() const {
		return sizeof (Minimize);
	}
	Size_t
	Minimize :: getVolume() const
	{
		Size_t volume = 0;
		volume += getAggregateVolume (comments_);
		return volume;
	}

	/****************************
	 *		Private members
	 ****************************/

	void
	Minimize :: startTheory() const
	{
		if (Config :: verbosity() > Config :: VERBOSE_MIN) {
			std :: cout << std :: endl;
		}
		Del :: statistics().push();
		const String& nameString = Table :: theories()->get (theoryName_);
		Del :: statistics().data()->setTheory (theoryName_);

		Del :: log()->message() << "//======================================" << endLine;
		Del :: log()->message() << "//  MINIMIZING THEORY: " << nameString << endLine;
		Del :: log()->message() << "//======================================" << endLine;
		Del :: log()->message() << endLine;
		Del :: log()->message() << *theory_ << endLine;
		Del :: statistics().data()->setOriginalTheorySize (theory_->getSize());
	}
	void
	Minimize :: minimizeTheory() const
	{
		if (Config :: verbosity() > Config :: VERBOSE_MIN) {
			//std :: cout << "\tminimizing ";
			const String& nameString = Table :: theories()->get (theoryName_);
			std :: cout << nameString;
			std :: cout <<  " ... " << std :: flush;
		}
		Del :: del()->timers().minimize().start();
		minimalTheory_ = theory_->clone();
		minimalTheory_->minimize();
		Del :: del()->timers().minimize().stop();
		if (Config :: verbosity() > Config :: VERBOSE_MIN) {
			std :: cout << "done in " << Del :: del()->timers().minimize() << std :: endl;
		}
		if (Config :: verbosity() > Config :: VERBOSE_MED) {
			std :: cout << "size = " << theory_->getSize() << " ";
			std :: cout << "formulas" <<  std :: endl;
			std :: cout << "redundancy = " << (theory_->getSize() - minimalTheory_->getSize()) << " ";
			std :: cout << "formulas" <<  std :: endl;
			std :: cout << "theory volume = ";
			memory :: Unit :: show (std :: cout, theory_->getVolume());
			std :: cout << std :: endl;
		}
		Del :: statistics().data()->minimizeTimer() = Del :: del()->timers().minimize();
		Del :: log()->message() << "/**************************************/" << endLine;
		Del :: log()->message() << "/*        MINIMAL THEORY:             */" << endLine;
		Del :: log()->message() << "/**************************************/" << endLine;
		Del :: log()->message() << endLine;
		Del :: log()->message() << *minimalTheory_ << endLine;
		Del :: statistics().data()->setMinimalTheorySize (minimalTheory_->getSize());

		//std :: cout << "minimalTheory_ = " << std :: endl;
		//std :: cout << *minimalTheory_ << std :: endl << std :: endl;
	}
	void
	Minimize :: finishTheory() const
	{
		const String& nameString = Table :: theories()->get (theoryName_);
		Del :: log()->message() << "//======================================" << endLine;
		Del :: log()->message() << "//  THEORY: " << nameString << " IS FINISHED" << endLine;
		Del :: log()->message() << "//======================================" << endLine;
		Del :: log()->message() << endLine << endLine << endLine;
		Del :: log()->message() << endLine << endLine << endLine;
	}
	const del :: Minimization*
	Minimize :: createMinimization() const
	{
		const value :: Theory minimizedName = Table :: theories()->fresh ("T");
		minimalTheory_->setName (minimizedName);
		Math :: source()->get()->addTheory (minimalTheory_);
		Math :: theories()->add (minimalTheory_);
		Minimization* minimization = new source :: Minimization (theoryName_, minimizedName);
		return minimization;
	}
}
}


