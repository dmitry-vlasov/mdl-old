/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_auxiliary_Timers.cpp                                 */
/* Description:     class for processing timers                              */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "mdl/auxiliary/mdl_auxiliary.hpp"

namespace mdl {
namespace auxiliary {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Timers :: Timers() :
	read_ (),
	build_ (),
	check_ (),
	compress_ (),
	reprove_ (),
	learn_ (),
	tune_ (),
	benchmark_ (),
	prove_ (),
	translate_ (),
	write_ (),
	total_ (),
	buildingNodes_ (),
	buildingEvidences_ (),
	buildingProofs_ ()
	{
		buildingNodes_.setShowCumulativeTime();
		buildingEvidences_.setShowCumulativeTime();
		buildingProofs_.setShowCumulativeTime();
	}
	Timers :: ~ Timers() {
	}

	inline Timer&
	Timers :: init() {
		return init_;
	}
	inline Timer&
	Timers :: release() {
		return release_;
	}
	inline Timer&
	Timers :: misc() {
		return misc_;
	}

	inline Timer&
	Timers :: read() {
		return read_;
	}
	inline Timer&
	Timers :: build() {
		return build_;
	}
	inline Timer&
	Timers :: check() {
		return check_;
	}
	inline Timer&
	Timers :: compress() {
		return compress_;
	}
	inline Timer&
	Timers :: reprove() {
		return reprove_;
	}
	inline Timer&
	Timers :: learn() {
		return learn_;
	}
	inline Timer&
	Timers :: tune() {
		return tune_;
	}
	inline Timer&
	Timers :: benchmark() {
		return benchmark_;
	}
	inline Timer&
	Timers :: prove() {
		return prove_;
	}
	inline Timer&
	Timers :: translate() {
		return translate_;
	}
	inline Timer&
	Timers :: write() {
		return write_;
	}
	inline Timer&
	Timers :: total() {
		return total_;
	}

	inline Timer&
	Timers :: buildingNodes() {
		return buildingNodes_;
	}
	inline Timer&
	Timers :: buildingEvidences() {
		return buildingEvidences_;
	}
	inline Timer&
	Timers :: buildingProofs() {
		return buildingProofs_;
	}

	inline const Timer&
	Timers :: read() const {
		return read_;
	}
	inline const Timer&
	Timers :: build() const {
		return build_;
	}
	inline const Timer&
	Timers :: check() const {
		return check_;
	}
	inline const Timer&
	Timers :: compress() const {
		return compress_;
	}
	inline const Timer&
	Timers :: reprove() const {
		return reprove_;
	}
	inline const Timer&
	Timers :: learn() const {
		return learn_;
	}
	inline const Timer&
	Timers :: tune() const {
		return tune_;
	}
	inline const Timer&
	Timers :: benchmark() const {
		return benchmark_;
	}
	inline const Timer&
	Timers :: prove() const {
		return prove_;
	}
	inline const Timer&
	Timers :: translate() const {
		return translate_;
	}
	inline const Timer&
	Timers :: write() const {
		return write_;
	}
	inline const Timer&
	Timers :: total () const {
		return total_;
	}

	inline const  Timer&
	Timers :: buildingNodes() const {
		return buildingNodes_;
	}
	inline const Timer&
	Timers :: buildingEvidences() const {
		return buildingEvidences_;
	}
	inline const Timer&
	Timers :: buildingProofs() const {
		return buildingProofs_;
	}

	void
	Timers :: stopAll()
	{
		init_.stop();
		release_.stop();
		misc_.stop();

		read_.stop();
		build_.stop();
		check_.stop();
		compress_.stop();
		reprove_.stop();
		learn_.stop();
		tune_.stop();
		benchmark_.stop();
		prove_.stop();
		translate_.stop();
		write_.stop();
		total_.stop();

		buildingNodes_.stop();
		buildingEvidences_.stop();
		buildingProofs_.stop();
	}

	void
	Timers :: clear()
	{
		init_.clear();
		release_.clear();
		misc_.clear();

		read_.clear();
		build_.clear();
		check_.clear();
		compress_.clear();
		reprove_.clear();
		learn_.clear();
		tune_.clear();
		benchmark_.clear();
		prove_.clear();
		translate_.clear();
		write_.clear();
		total_.clear();

		buildingNodes_.clear();
		buildingEvidences_.clear();
		buildingProofs_.clear();
	}

using manipulator :: endLine;
using manipulator :: space;
using manipulator :: tab;

	// object :: Object interface
	void
	Timers :: commitSuicide() {
		delete this;
	}
	Size_t
	Timers :: getVolume() const {
		return 0;
	}
	Size_t
	Timers :: getSizeOf() const {
		return sizeof (Timers);
	}
	void
	Timers :: show (String& string) const
	{
		string << "timings:" << endLine;
		string << "-------------------------" << endLine;
		if (init_.isUsed())      { string << tab << "init:      " << init_      << endLine; }
		if (read_.isUsed())      { string << tab << "read:      " << read_      << endLine; }
		if (build_.isUsed())     { string << tab << "build:     " << build_     << endLine; }
		if (check_.isUsed())     { string << tab << "check:     " << check_     << endLine; }
		if (compress_.isUsed())  { string << tab << "compress:  " << compress_  << endLine; }
		if (reprove_.isUsed())   { string << tab << "reprove:   " << reprove_   << endLine; }
		if (learn_.isUsed())     { string << tab << "learn:     " << learn_     << endLine; }
		if (tune_.isUsed())      { string << tab << "tune:      " << tune_      << endLine; }
		if (benchmark_.isUsed()) { string << tab << "benchmark: " << tune_      << endLine; }
		if (prove_.isUsed())     { string << tab << "prove:     " << prove_     << endLine; }
		if (translate_.isUsed()) { string << tab << "translate: " << translate_ << endLine; }
		if (write_.isUsed())     { string << tab << "write:     " << write_     << endLine; }
		if (release_.isUsed())   { string << tab << "release:   " << release_   << endLine; }
		if (buildingNodes_.isUsed() || buildingEvidences_.isUsed() || buildingProofs_.isUsed()) {
			string << tab << "building: " << endLine;
			if (buildingNodes_.isUsed())     { string << tab << tab << "nodes:     " << buildingNodes_     << endLine; }
			if (buildingEvidences_.isUsed()) { string << tab << tab << "evidences: " << buildingEvidences_ << endLine; }
			if (buildingProofs_.isUsed())    { string << tab << tab << "proofs:    " << buildingProofs_    << endLine; }
		}
	}

	/**********************************
	 *		Private static members
	 **********************************/

	Timer Timers :: init_;
	Timer Timers :: release_;
	Timer Timers :: misc_;
}
}


