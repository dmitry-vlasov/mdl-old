/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_memory_UsageMessage.cpp                             */
/* Description:     displays memory usage message                            */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef NSTD_MEMORY_USAGE_MESSAGE_CPP_
#define NSTD_MEMORY_USAGE_MESSAGE_CPP_

namespace nstd {
namespace memory {

	/****************************
	 *		Public members
	 ****************************/

	UsageMessage :: UsageMessage
	(
		const Ptrdiff_t overallVolume,
		const Ptrdiff_t currentVolume,
		const char message[],
		const char delimiter,
		const bool showPreciseValue,
		const Unit :: Unit_ measureUnit
	) :
	measureUnit_
	(
		measureUnit == Unit :: AUTO ?
		Unit :: calculate (currentVolume) :
		measureUnit
	),
	overallVolume_ (overallVolume),
	currentVolume_ (currentVolume),
	message_ (message),
	delimiter_ (delimiter),
	showPreciseValue_ (showPreciseValue) {
	}

	template<class S>
	void
	UsageMessage :: show (S& s) const
	{
		const double percentVolume =
			(overallVolume_ == 0) ? 0 :
			static_cast<const double> (currentVolume_) * 100 / overallVolume_;
		const double normalizedVolume =
			static_cast<const double> (currentVolume_) / measureUnit_;

		s << message_ << ":" << delimiter_ << normalizedVolume;
		s << chars :: SPACE << unit() << delimiter_;
		if (overallVolume_ > 0) {
			if (showPreciseValue_ && currentVolume_ > 0) {
				s << "(" << currentVolume_ << " b)" << delimiter_;
			}
			if (overallVolume_ != currentVolume_ &&
				currentVolume_ > 0) {
				s << "= " << percentVolume << " %";
			}
		}
	}
	template<>
	void
	UsageMessage :: show<std :: ostream> (std :: ostream& s) const
	{
		const double percentVolume =
			(overallVolume_ == 0) ? 0 :
			static_cast<const double> (currentVolume_) * 100 / overallVolume_;
		const double normalizedVolume =
			static_cast<const double> (currentVolume_) / measureUnit_;

		s << message_ << ":" << std :: setprecision (3) << delimiter_ << normalizedVolume;
		s << chars :: SPACE << unit() << delimiter_;
		if (overallVolume_ > 0) {
			if (showPreciseValue_ && currentVolume_ > 0) {
				s << std :: setprecision (3) << "(" << currentVolume_ << " b)" << delimiter_;
			}
			if (overallVolume_ != currentVolume_ &&
				currentVolume_ > 0) {
				s << std :: setprecision (3) << "= " << percentVolume << " %";
			}
		}
	}

	/****************************
	 *		Private members
	 ****************************/

	inline const char*
	UsageMessage :: unit() const {
		return Unit :: unit (measureUnit_);
	}

	/****************************
	 *		Operators
	 ****************************/

	template<class S>
	S&
	operator << (S& s, const UsageMessage& message)
	{
		message.show (s);
		return s;
	}
}
}

#endif /*NSTD_MEMORY_USAGE_MESSAGE_CPP_*/
