/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_form_Contents.hpp                                    */
/* Description:     contents of a theory                                     */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/


#ifndef MDL_FORM_CONTENTS_HPP_
#define MDL_FORM_CONTENTS_HPP_

#include "mdl/interface/mdl_interface.hpp"
#include "mdl/form/mdl_form_Identifiable.hpp"

namespace mdl {
namespace form {

class Contents :
	public mdl :: Contents,
	public Identifiable,
	public Scalar<Contents> {
public :
	Contents
	(
		const Location&,
		const mdl :: Comments* const,
		const value :: Name,
		mdl :: Theory*
	);
	virtual ~ Contents();

	// mdl :: Components interface
	virtual index :: Assertion getSize() const;
	virtual void addComponentLast (object :: Verifiable* component);
	virtual void addComponentNextTo
	(
		object :: Verifiable* component,
		const object :: Verifiable* sibling
	);
	virtual object :: Verifiable* getComponent (const index :: Assertion);
	virtual const object :: Verifiable* getComponent (const index :: Assertion) const;

	// object :: Verifiable interface
	virtual void check();
	virtual void compress();
	virtual void reprove();
	virtual void prove();
	virtual bool isVerified() const;
	virtual void mine (String&) const;

	// object :: Buildable interface
	virtual void build();

	// object :: Writable interface
	virtual void translate (String&) const;
	virtual void replicate (String&) const;
	virtual void write (Output&) const;
	virtual bool lookup() const;
	virtual object :: Writable* find();
	virtual const object :: Writable* find() const;

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;

private :
	friend class mdl :: parser :: Contents;
	typedef
		vector :: object :: Verifiable
		ComponentVector_;
	typedef
		vector :: Vector
		<
			object :: Verifiable*,
			storage :: ByValue,
			allocator :: Heap
		>
		VerifiableVector_;

	enum {
		INITIAL_COMPONENT_VECTOR_CAPACITY = 256
	};

	void checkSingleThreaded();
	void buildSingleThreaded();

#ifdef MULTY_THREADED
	friend void* checkInThread (void* pointer);
	friend void* buildInThread (void* pointer);
	struct Arguments_ {
		Arguments_() :
		threadIndex_ (0),
		threadCount_ (0),
		vector_ (NULL) {
		}
		int threadIndex_;
		int threadCount_;
		const VerifiableVector_* vector_;
	};
	void doJobThreaded (void* func (void*), const VerifiableVector_*);
#endif

	mdl :: Theory*    innerTheory_;
	ComponentVector_  componentVector_;
	VerifiableVector_ firstPassVector_;
	VerifiableVector_ secondPassVector_;
	VerifiableVector_ thirdPassVector_;
	bool isVerified_;
};

#ifdef MULTY_THREADED
	void* checkInThread (void* pointer);
	void* buildInThread (void* pointer);
#endif

}
}

#endif /*MDL_FORM_CONTENTS_HPP_*/
