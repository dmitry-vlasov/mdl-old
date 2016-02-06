/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_container_storage_ByAggregation.hpp                 */
/* Description:     aggregation storage policy for containers                */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

namespace nstd {
namespace container {
namespace storage {

template
<
	class T	// Stored type
>
class ByAggregation {
public :
	typedef T Type_;
	typedef const T& Argument_;
	typedef T Value_;
	typedef T& Reference_;
	typedef const T& const_Reference_;

	ByAggregation();
	ByAggregation (Argument_);
	ByAggregation (const ByAggregation&);

	Value_ getValue() const;
	Reference_ getReference();
	const_Reference_ getReference() const;

	bool operator == (Argument_) const;
	bool operator != (Argument_) const;
	bool operator < (Argument_) const;
	bool operator <= (Argument_) const;
	bool operator > (Argument_) const;
	bool operator >= (Argument_) const;
	void operator = (Argument_);

	bool operator == (const ByAggregation&) const;
	bool operator != (const ByAggregation&) const;
	bool operator < (const ByAggregation&) const;
	bool operator <= (const ByAggregation&) const;
	bool operator > (const ByAggregation&) const;
	bool operator >= (const ByAggregation&) const;
	void operator = (const ByAggregation&);

	void undefine();

	static void swap (ByAggregation&, ByAggregation&);

	// nstd :: Object interface
	Size_t getVolume() const;
	Size_t getSizeOf() const;

protected :
	Type_ data_;
};

}
}
}


