/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File name:       del_auxiliary_Statistics_Data.hpp                        */
/* Description:     class for program data statistics counters               */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef DEL_AUXILIARY_STATISTICS_DATA_HPP_
#define DEL_AUXILIARY_STATISTICS_DATA_HPP_

#include "del/interface/del_interface_Object.hpp"
#include "del/del.dpp"

namespace del {
namespace auxiliary {

class Statistics :: Data :
	public Object,
	public Scalar<Data> {
public :
	Data();
	virtual ~ Data();

	void setTheory (const value :: Theory);
	void setOriginalTheorySize (const value :: Integer);
	void setMinimalTheorySize (const value :: Integer);
	void setNormalTheorySize (const value :: Integer);
	void setPrimitiveTheorySize (const value :: Integer);
	void setDecomposedTheorySize (const value :: Integer);
	void setAssembledTheorySize (const value :: Integer);

	void setDecompositionQuality (const value :: Integer);

	void incSplit();
	void incExistsLeft();
	void incExistsRight();
	void incConjunction (const value :: Integer);

	Timer& minimizeTimer();
	Timer& normalizeTimer();
	Timer& primitivizeTimer();
	Timer& decomposeTimer();
	Timer& assembleTimer();
	Timer& compileTimer();

	vector :: value :: Integer& signatureDecomposition (const bool);
	vector :: value :: Integer& theoryDecomposition (const bool);

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	void otputDecompositionStat (String&, const char* message, const vector :: value :: Integer& data) const;

	value :: Theory theory_;

	value :: Integer originalTheorySize_;
	value :: Integer minimalTheorySize_;
	value :: Integer normalTheorySize_;
	value :: Integer primitiveTheorySize_;
	value :: Integer decomposedTheorySize_;
	value :: Integer assembledTheorySize_;

	value :: Integer decompositionQuality_;

	value :: Integer split_;
	value :: Integer existsLeft_;
	value :: Integer existsRight_;
	value :: Integer conjunction_;
	value :: Integer conjCounter_;

	Timer minimizeTimer_;
	Timer normalizeTimer_;
	Timer primitivizeTimer_;
	Timer decomposeTimer_;
	Timer assembleTimer_;
	Timer compileTimer_;

	vector :: value :: Integer originalSignatureDecomposition_;
	vector :: value :: Integer originalTheoryDecomposition_;
	vector :: value :: Integer decomposedSignatureDecomposition_;
	vector :: value :: Integer decomposedTheoryDecomposition_;
	enum {
		INITIAL_DECOMPOSITION_CAPACITY = 32
	};
};

}
}

#endif /*DEL_AUXILIARY_STATISTICS_DATA_HPP_*/
