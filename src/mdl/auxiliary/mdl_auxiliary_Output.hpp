/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_auxiliary_Output.hpp                                 */
/* Description:     output routines class                                    */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "mdl/interface/mdl_interface.dpp"

namespace mdl {
namespace auxiliary {

class Output :
	public nstd :: Object,
	public Scalar<Output> {
public :
	Output (const char*);
	Output (const String&);
	virtual ~ Output();

	void open();
	void close();
	void write (const object :: Writable* const);
	String& buffer();

	// nstd :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (nstd :: String<>&) const;

private :
	typedef Size_t Count_;

	OutputFileStream fileStream_;
	String filePath_;
	String buffer_;
	Count_ objectCount_;

	enum {
		OUTPUT_FILE_FLUSH_COUNT_THRESHOLD = 32, //32,
		INITIAL_OUTPUT_BUFFER_CAPACITY = 1024 * 64
	};
};

}
}


