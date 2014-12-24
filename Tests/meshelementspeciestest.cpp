#pragma warning ( disable: 4996 )
#include "gtest/gtest.h"
#include <MeshElementSpecies.h>
#include <boundaryProviders.h>
#include <VoronoiMesh.h>
using std::cout;
using std::endl;
using namespace spatial;
using namespace moving_boundary; 
TEST(persist,mesNeighbor) {
	using moving_boundary::FrontPointType;
	std::vector<GeoLimit> limits;
	limits.push_back(GeoLimit(0,5));
	limits.push_back(GeoLimit(0,3));
	//spatial::VCellFront<moving_boundary::CoordinateType> front(limits, 175,1.5, lv,vel); 
	using spatial::Point2D; 
	FrontProvider<CoordinateType> * fp = moving_boundary::circleFront(0,0,1,0.1,0);
	const std::array<CoordinateType,2> origin = { 0, 0};
	const std::array<CoordinateType,2> edge = { 5, 2};
	const std::array<size_t,2> extent = { 35, 35 }; 

	VoronoiMesh::MBMeshDef trial(origin,edge,extent);

	//typedef moving_boundary::MeshElementSpecies MPoint2;
	VoronoiMesh::MBMesh mesh(trial);
	std::array<size_t,2> s= { 3, 4}; 
	MeshElementSpecies & sample = mesh.get( s );
	s[0] += 3;
	s[1] += 11;
	MeshElementSpecies & nbElement = mesh.get ( s); 
	MeshElementSpecies * p1 = mesh.query( s );
	MeshElementNeighbor nb( &nbElement);
	nb.distanceTo = 3.14;
	nb.edgeLength = 2.71;
	MeshElementNeighbor::registerType( );
	{
		std::ofstream out("meshNeighbor.dat", std::ios::binary|std::ios::trunc);
		vcell_persist::WriteFormatter wf(out, 1);
		nb.persist(out,sample);
	}
	std::ifstream in("meshNeighbor.dat", std::ios::binary);
	vcell_persist::ReadFormatter wf(in, 1);
	MeshElementNeighbor back(in,sample); 
	MeshElementSpecies * p2 = mesh.query( s );
	ASSERT_TRUE(back == nb);
}

TEST(persist,mes) {
	using moving_boundary::FrontPointType;
	std::vector<GeoLimit> limits;
	limits.push_back(GeoLimit(0,5));
	limits.push_back(GeoLimit(0,3));
	//spatial::VCellFront<moving_boundary::CoordinateType> front(limits, 175,1.5, lv,vel); 
	using spatial::Point2D; 
	FrontProvider<CoordinateType> * fp = moving_boundary::circleFront(0,0,1,0.1,0);
	const std::array<CoordinateType,2> edge = { 5, 2};
	const std::array<size_t,2> extent = { 35, 35 }; 

	const std::array<CoordinateType,2> origin = { 0, 0};
	VoronoiMesh::MBMeshDef trial(origin,edge,extent);

	//typedef moving_boundary::MeshElementSpecies MPoint2;
	VoronoiMesh::MBMesh mesh(trial);
	std::array<size_t,2> s= { 3, 4}; 
	MeshElementSpecies & sample = mesh.get( s );
	MeshElementSpecies::registerType( );
	SVector<moving_boundary::VelocityType,2> vel = sample.getVelocity( );
	vel(cX) = 3.4;
	vel(cY) = 9.5;
	sample.setVelocity(vel);
	{
		std::ofstream out("mes.dat", std::ios::binary|std::ios::trunc);
		vcell_persist::WriteFormatter wf(out, 1);
		sample.persist(out);
	}
	std::ifstream in("mes.dat", std::ios::binary);
	vcell_persist::ReadFormatter wf(in, 1);
	MeshElementSpecies back(mesh,in); 
	ASSERT_TRUE(back.volumePD( ) == sample.volumePD( ));
	ASSERT_TRUE(back.concentration(0) == sample.concentration(0));
	ASSERT_TRUE(back.mass(0) == sample.mass(0));
	ASSERT_TRUE(back.getVelocity( ) == sample.getVelocity( ) );
}

TEST(persist,mesh) {
	using moving_boundary::FrontPointType;
	std::vector<GeoLimit> limits;
	limits.push_back(GeoLimit(0,5));
	limits.push_back(GeoLimit(0,3));
	//spatial::VCellFront<moving_boundary::CoordinateType> front(limits, 175,1.5, lv,vel); 
	using spatial::Point2D; 
	FrontProvider<CoordinateType> * fp = moving_boundary::circleFront(0,0,1,0.1,0);
	const std::array<CoordinateType,2> origin = { 0, 0};
	const std::array<CoordinateType,2> edge = { 5, 2};
	const std::array<size_t,2> extent = { 35, 35 }; 

	VoronoiMesh::MBMeshDef trial(origin,edge,extent);

	//typedef moving_boundary::MeshElementSpecies MPoint2;
	VoronoiMesh::MBMesh mesh(trial);
	std::array<size_t,2> s= { 3, 4}; 
	MeshElementSpecies::registerType( );
	SVector<moving_boundary::VelocityType,2> vel(3.4,9.5);
	{
		MeshElementSpecies & sample = mesh.get( s );
		sample.setVelocity(vel);
		mesh.registerType( );

		{
			std::ofstream out("mesh.dat", std::ios::binary|std::ios::trunc);
			vcell_persist::WriteFormatter wf(out, 1);
			mesh.persist(out);
		}

		{
			std::ofstream out("mesh2.dat", std::ios::binary|std::ios::trunc);
			vcell_persist::WriteFormatter wf(out, 7, true);
			mesh.persist(out);
		}
	}
	{
		std::ifstream in("mesh.dat", std::ios::binary);
		vcell_persist::ReadFormatter wf(in, 1);
		VoronoiMesh::MBMesh back(in); 
		MeshElementSpecies & sample = back.get( s );
		ASSERT_TRUE(sample.getVelocity( ) == vel);
	}
	{
		std::ifstream in("mesh2.dat", std::ios::binary);
		vcell_persist::ReadFormatter wf(in, 7);
		VoronoiMesh::MBMesh back(in); 
		MeshElementSpecies & sample = back.get( s );
		ASSERT_TRUE(sample.getVelocity( ) == vel);
	}
}

struct Salad {};

struct F {
	int operator( )(Salad *in) {
		return 5;
	}
};

TEST(persist,dogx) {
	std::vector<int> v;
	std::vector<Salad *> salad;
	std::transform(salad.begin( ),salad.end( ),v.begin( ),F( ));
}
TEST(mes,states) {
	using namespace moving_boundary::MeshElementStateful;
	for (int i = 0; i < 30; i++) {
		State s = static_cast<State>(i);
		std::cout << s << std::endl;
	}
}
