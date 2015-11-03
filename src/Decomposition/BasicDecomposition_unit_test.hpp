#ifndef BASICDECOMPOSITION_UNIT_TEST_HPP
#define BASICDECOMPOSITION_UNIT_TEST_HPP

#include "BasicDecomposition.hpp"
#include "util/mathutil.hpp"

BOOST_AUTO_TEST_SUITE( BasicDecomposition_test )

#define SUB_UNIT_FACTOR 1024

BOOST_AUTO_TEST_CASE( BasicDecomposition_test_use)
{
	// Vcluster
	Vcluster & vcl = *global_v_cluster;

	// Initialize the global VCluster
	init_global_v_cluster(&boost::unit_test::framework::master_test_suite().argc,&boost::unit_test::framework::master_test_suite().argv);

	//! [Create CartDecomposition]
	BasicDecomposition<3,float> dec(vcl);

	// Physical domain
	Box<3,float> box({0.0,0.0,0.0},{1.0,1.0,1.0});
	size_t div[3];

	// Get the number of processor and calculate the number of sub-domain
	// for each processor (SUB_UNIT_FACTOR=64)
	size_t n_proc = vcl.getProcessingUnits();
	size_t n_sub = n_proc * SUB_UNIT_FACTOR;

	// Set the number of sub-domains on each dimension (in a scalable way)
	for (int i = 0 ; i < 3 ; i++)
	{div[i] = openfpm::math::round_big_2(pow(n_sub,1.0/3));}

	// Define ghost
	Ghost<3,float> g(0.01);

	// Decompose
	dec.setParameters(div,box,g);

	// create a ghost border
	dec.calculateGhostBoxes();

	//! [Create BasicDecomposition]

	// For each calculated ghost box
	for (size_t i = 0 ; i < dec.getNIGhostBox() ; i++)
	{
		SpaceBox<3,float> b = dec.getIGhostBox(i);
		size_t proc = dec.getIGhostBoxProcessor(i);

		// sample one point inside the box
		Point<3,float> p = b.rnd();

		// Check that ghost_processorsID return that processor number
		const openfpm::vector<size_t> & pr = dec.template ghost_processorID<BasicDecomposition<3,float>::processor_id>(p);

		bool found = false;

		for (size_t j = 0; j < pr.size() ; j++)
		{
			if (pr.get(j) == proc)
			{found = true; break;}
		}

		if (found == false)
		{
			const openfpm::vector<size_t> pr3 = dec.template ghost_processorID<BasicDecomposition<3,float>::processor_id>(p);
		}

		BOOST_REQUIRE_EQUAL(found,true);
	}

	// Check the consistency

	bool val = dec.check_consistency();
	BOOST_REQUIRE_EQUAL(val,true);
}

BOOST_AUTO_TEST_SUITE_END()


#endif