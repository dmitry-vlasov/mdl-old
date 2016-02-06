/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_auxiliary_statistics_Sample.hpp                      */
/* Description:     sample class for statistics data                         */
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
namespace statistics {

class Sample :
	public nstd :: Object,
	public Scalar<Sample, allocator :: Heap> {
public :
	Sample (const Size_t initialSampleCapacity = INITIAL_SAMPLE_CAPACITY);
	virtual ~ Sample();

	void add (const double);
	double getLastValue() const;
	Size_t getSize() const;

	double relativize (const double) const;
	double normalize (const double) const;
	double relativize() const;
	double normalize() const;

	double getMax() const;
	double getMin() const;
	double getAverage() const;
	double getDispersion() const;
	double getSigma() const;
	bool updated() const;

	template<class S>
	void showBrief (S&) const;

	// nstd :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (nstd :: String<>&) const;

private :

	typedef
		typename vector :: Vector
		<
			double,
			storage :: ByValue,
			allocator :: Heap
		>
		Sample_;

	enum {
		INITIAL_SAMPLE_CAPACITY = 1024
	};

	void update() const;
	void calculateAverage() const;
	void calculateDispersion() const;

	Sample_ sample_;
	double  lastValue_;

	mutable double max_;
	mutable double min_;
	mutable double average_;
	mutable double dispersion_;
	mutable double sigma_;
	mutable bool   updated_;

	pthread_mutex_t mutex_;
};

}
}
}


