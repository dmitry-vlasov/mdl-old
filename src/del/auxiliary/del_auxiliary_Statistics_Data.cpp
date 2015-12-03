/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File name:       del_auxiliary_Statistics_Data.cpp                        */
/* Description:     class for program data statistics counters               */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/


#ifndef DEL_AUXILIARY_STATISTICS_DATA_CPP_
#define DEL_AUXILIARY_STATISTICS_DATA_CPP_

#include "del/del_Del.hpp"

namespace del {
namespace auxiliary {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Statistics :: Data :: Data () :
	theory_ (value :: undefined :: THEORY),
	originalTheorySize_ (0),
	minimalTheorySize_ (0),
	normalTheorySize_ (0),
	primitiveTheorySize_ (0),
	decomposedTheorySize_ (0),
	assembledTheorySize_ (0),
	decompositionQuality_ (0),
	split_ (0),
	existsLeft_ (0),
	existsRight_ (0),
	conjunction_ (0),
	conjCounter_ (0),
	minimizeTimer_ (),
	normalizeTimer_ (),
	primitivizeTimer_ (),
	decomposeTimer_ (),
	assembleTimer_ (),
	compileTimer_ (),
	originalSignatureDecomposition_ (INITIAL_DECOMPOSITION_CAPACITY),
	originalTheoryDecomposition_ (INITIAL_DECOMPOSITION_CAPACITY),
	decomposedSignatureDecomposition_ (INITIAL_DECOMPOSITION_CAPACITY),
	decomposedTheoryDecomposition_ (INITIAL_DECOMPOSITION_CAPACITY) {
	}
	Statistics :: Data :: ~ Data() {
	}

	inline void
	Statistics :: Data :: setTheory (const value :: Theory theory) {
		theory_ = theory;
	}
	inline void
	Statistics :: Data :: setOriginalTheorySize (const value :: Integer originalTheorySize) {
		originalTheorySize_ = originalTheorySize;
	}
	inline void
	Statistics :: Data :: setMinimalTheorySize (const value :: Integer minimalTheorySize) {
		minimalTheorySize_ = minimalTheorySize;
	}
	inline void
	Statistics :: Data :: setNormalTheorySize (const value :: Integer normalTheorySize) {
		normalTheorySize_ = normalTheorySize;
	}
	inline void
	Statistics :: Data :: setPrimitiveTheorySize (const value :: Integer primitiveTheorySize) {
		primitiveTheorySize_ = primitiveTheorySize;
	}
	inline void
	Statistics :: Data :: setDecomposedTheorySize (const value :: Integer decomposedTheorySize) {
		decomposedTheorySize_ = decomposedTheorySize;
	}
	inline void
	Statistics :: Data :: setAssembledTheorySize (const value :: Integer assembledTheorySize) {
		assembledTheorySize_ = assembledTheorySize;
	}

	inline void
	Statistics :: Data :: setDecompositionQuality (const value :: Integer decompositionQuality) {
		decompositionQuality_ = decompositionQuality;
	}

	inline void
	Statistics :: Data :: incSplit() {
		++ split_;
	}
	inline void
	Statistics :: Data :: incExistsLeft()
	{
		++ existsLeft_;
	}
	inline void
	Statistics :: Data :: incExistsRight() {
		++ existsRight_;
	}
	inline void
	Statistics :: Data :: incConjunction (const value :: Integer count) {
		++ conjunction_;
		conjCounter_ += count;
	}

	inline Timer&
	Statistics :: Data :: minimizeTimer() {
		return minimizeTimer_;
	}
	inline Timer&
	Statistics :: Data :: normalizeTimer() {
		return normalizeTimer_;
	}
	inline Timer&
	Statistics :: Data :: primitivizeTimer() {
		return primitivizeTimer_;
	}
	inline Timer&
	Statistics :: Data :: decomposeTimer() {
		return decomposeTimer_;
	}
	inline Timer&
	Statistics :: Data :: assembleTimer() {
		return assembleTimer_;
	}
	inline Timer&
	Statistics :: Data :: compileTimer() {
		return compileTimer_;
	}

	inline vector :: value :: Integer&
	Statistics :: Data :: signatureDecomposition (const bool isOriginal)
	{
		if (isOriginal) {
			return originalSignatureDecomposition_;
		} else {
			return decomposedSignatureDecomposition_;
		}
	}
	inline vector :: value :: Integer&
	Statistics :: Data :: theoryDecomposition (const bool isOriginal)
	{
		if (isOriginal) {
			return originalTheoryDecomposition_;
		} else {
			return decomposedTheoryDecomposition_;
		}
	}

using manipulator :: endLine;
using manipulator :: space;
using manipulator :: tab;

	// object :: Object implementation
	void
	Statistics :: Data :: commitSuicide() {
		delete this;
	}
	Size_t
	Statistics :: Data :: getVolume() const
	{
		Size_t volume = 0;
		volume += originalSignatureDecomposition_.getVolume();
		volume += originalTheoryDecomposition_.getVolume();
		volume += decomposedSignatureDecomposition_.getVolume();
		volume += decomposedTheoryDecomposition_.getVolume();
		return volume;
	}
	Size_t
	Statistics :: Data :: getSizeOf() const {
		return sizeof (Data);
	}
	void
	Statistics :: Data :: show (String& string) const
	{
		const String& theoryName = Table :: theories()->get (theory_);
		string << "theory " << theoryName << " statistics:" << endLine;
		string << "------------------------------" << endLine;
		string << "original  theory size:" << tab << originalTheorySize_ << endLine;
		string << "minimal   theory size:" << tab << minimalTheorySize_ << endLine;
		string << "normal    theory size:" << tab << normalTheorySize_ << endLine;
		string << "primitive theory size:" << tab << primitiveTheorySize_ << endLine;
		string << "dec-sed   theory size:" << tab << decomposedTheorySize_ << endLine;
		string << "assembled theory size:" << tab << assembledTheorySize_ << endLine;
		string << endLine;
		string << "decomposition quality:" << tab << decompositionQuality_ << endLine;
		string << endLine;
		string << "minimization    time:" << tab << minimizeTimer_ << endLine;
		string << "normalization   time:" << tab << normalizeTimer_ << endLine;
		string << "primitivization time:" << tab << primitivizeTimer_ << endLine;
		string << "decomposition   time:" << tab << decomposeTimer_ << endLine;
		string << "assembling      time:" << tab << assembleTimer_ << endLine;
		string << "compile         time:" << tab << compileTimer_ << endLine;
		string << endLine;
		string << "split        cases:" << tab << split_ << endLine;
		string << "left exists  cases:" << tab << existsLeft_ << endLine;
		string << "right exists cases:" << tab << existsRight_ << endLine;
		string << "conjunction  cases:" << tab << conjunction_ << endLine;
		string << "conjunction  count:" << tab << conjCounter_ << endLine;
		string << endLine;
		string << "-----------------------------" << endLine;
		otputDecompositionStat (string, "syntactic signature decomposition: ", originalSignatureDecomposition_);
		otputDecompositionStat (string, "syntactic theory decomposition: ", originalTheoryDecomposition_);
		string << "-----------------------------" << endLine;
		otputDecompositionStat (string, "signature decomposition: ", decomposedSignatureDecomposition_);
		otputDecompositionStat (string, "theory decomposition: ", decomposedTheoryDecomposition_);
		string << "-----------------------------" << endLine;
	}

	/****************************
	 *		Private members
	 ****************************/

	void
	Statistics :: Data :: otputDecompositionStat
	(
		String& string,
		const char* message,
		const vector :: value :: Integer& data
	) const
	{
		if (data.getSize() > 0) {
			string << message << data.getSize() << " ";
			string << "components" << endLine;
			string << "component cardinalities: ";
			for (value :: Integer i = 0; i < data.getSize(); ++ i) {
				const value :: Integer componentCard = data.getValue (i);
				string << componentCard;
				if (i < data.getSize() - 1) {
					string << ", ";
				} else {
					string << endLine;
				}
			}
			string << endLine;
		}
	}
}
}

#endif /*DEL_AUXILIARY_STATISTICS_DATA_CPP_*/
