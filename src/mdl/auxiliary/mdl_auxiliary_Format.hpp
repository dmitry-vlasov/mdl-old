/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_auxiliary_Format.hpp                                 */
/* Description:     the base i/o components terminal reporting               */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_AUXILIARY_FORMAT_HPP_
#define MDL_AUXILIARY_FORMAT_HPP_

#include "mdl/interface/mdl_interface.hpp"
#include "mdl/auxiliary/mdl_auxiliary.dpp"

namespace mdl {
namespace auxiliary {

class Format :
	public object :: Object,
	public Scalar<Format> {
public :
	Format (const value :: Integer = 0);
	Format
	(
		Format&,
		const bool keepVerbosity = false,
		const bool keepDepth = false
	);
	virtual ~ Format();

	value :: Integer getDepth() const;
	value :: Integer getVerbosity() const;
	void setVerbosity (const value :: Integer);
	bool isPrintable() const;
	void setPrintableSubformat (const bool = true);
	const Timer& getTimer();

	String& message();
	void setOutput(String&);
	void unsetOutput();

	void showStart (const Time = -1);
	void showFinal();
	void showMessage();
	void typeIndent (String&) const;

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	template<typename S>
	void makeIndent (S&) const;
	bool hasPrintableSubformat() const;
	void outputFormattedMessage();

	enum {
		INITIAL_MESSAGE_CAPACITY = 32
	};

	typedef
		vector :: Vector
		<
			const Format*,
			storage :: ByValue,
			allocator :: Heap
		>
		FormatVector_;

	Format* up_;
	Timer timer_;
	value :: Integer depth_;
	value :: Integer verbosity_;
	FormatVector_ down_;
	String  message_;
	String  formatted_;
	String* output_;
	value :: Real timeLimit_;
	bool hasPrintableSubformat_;
};

}
}

#endif /*MDL_AUXILIARY_FORMAT_HPP_*/
