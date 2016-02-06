/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_form_proof_Proof_Refiner.hpp                         */
/* Description:     proof refining utility                                   */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "mdl/interface/mdl_interface.hpp"

namespace mdl {
namespace form {
namespace proof {

class Proof :: Refiner {
public :
	static index :: Assertion getCompressedCount();
	static index :: Step getOriginalProofLength();
	static index :: Step getCompressedProofLength();
	static double getCompressionFactor();

	static bool isCompressable (const mdl :: Assertion*);
	static void beforeCompression (const mdl :: Proof*);
	static void afterCompression (const mdl :: Proof*);

	static void init();
	static void release();

	static Size_t getVolume();
	static Size_t getSizeOf();
	static void show (String&);

private :
	static void calculateAverageLengthVector();
	static void calculateTheoremVector();
	static bool goodLength (const index :: Step, const index :: Step);

	typedef
		vector :: Vector
		<
			const mdl :: Assertion*,
			storage :: ByValue,
			allocator :: Heap
		>
		Vector_;

	// compression attributes
	static index :: Assertion compressedCount_;
	static index :: Step originalProofLength_;
	static index :: Step compressedProofLength_;
	static double compressionFactor_;
	enum {
		COMPRESSION_LOWER_BOUNDARY_THRESHOLD = 3,
		COMPRESSION_PERCENT_THRESHOLD = 25 // percent of the average length
	};

	static Vector_* theoremVector_;
	static vector :: value :: Integer* averageProofLength_;
};

}
}
}


