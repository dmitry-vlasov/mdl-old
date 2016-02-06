/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_console_Console.hpp                                  */
/* Description:     mdl console for manual control                           */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

namespace mdl {
namespace console {

class Console :
	public object :: Object,
	public Scalar<Console> {
public :
	Console (Engine* engine);
	virtual ~ Console();

	void run();
	String& outputBuffer();
	static Console* get();

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	enum {
		INITIAL_COMMAND_VECTOR_CAPACITY = 32,
		INITIAL_BUFFER_CAPACITY  = 4096
	};
	typedef
		vector :: Vector
		<
			Command,
			storage :: ByPointer,
			allocator :: Heap
		>
		CommandVector_;

	static Console* console_;

	Engine* engine_;
	CommandVector_ commandVector_;
	String         outputBuffer_;
	bool exit_;
};

}
}


