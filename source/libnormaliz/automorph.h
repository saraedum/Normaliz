/*
 * Normaliz
 * Copyright (C) 2007-2014  Winfried Bruns, Bogdan Ichim, Christof Soeger
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * As an exception, when this program is distributed through (i) the App Store
 * by Apple Inc.; (ii) the Mac App Store by Apple Inc.; or (iii) Google Play
 * by Google Inc., then that store may impose any digital rights management,
 * device limits and/or redistribution restrictions that are required by its
 * terms of service.
 */

#ifndef AUTOMORPHISM_H
#define AUTOMORPHISM_H

#include <boost/dynamic_bitset.hpp>
#include "libnormaliz/matrix.h"
#include "libnormaliz/nmz_nauty.h"

namespace libnormaliz {
using namespace std;

template<typename Integer> class Cone;
template<typename Integer> class Full_Cone;

template<typename Integer>
class Automorphism_Group {
    
    template<typename> friend class Cone;
    template<typename> friend class Full_Cone;
    
    Matrix<Integer> Gens, LinForms;

    vector<vector<key_t> > GenPerms; 
    vector<vector<key_t> > LinFormPerms;
    
    vector<vector<key_t> > GenOrbits;
    vector<vector<key_t> > LinFormOrbits;
    
    vector<Matrix<Integer> > LinMaps;
    
    mpz_class order;
    
    bool from_ambient_space;
    bool LinMaps_computed;
    bool graded;
    bool inhomogeneous;
    
    bool make_linear_maps_primal();
    void gen_data_via_lin_maps();
    void reset();
    
public:
    
    mpz_class getOrder() const;
    vector<vector<key_t> > getGenPerms() const;
    vector<vector<key_t> > getLinFormPerms() const;
    vector<vector<key_t> > getGenOrbits() const;
    vector<vector<key_t> > getLinFormOrbits() const;
    vector<Matrix<Integer> > getLinMaps() const;
    bool isFromAmbientSpace() const;
    bool isGraded() const;
    bool isInhomogeneous() const;
    bool isLinMapsComputed() const;
    void setFromAmbeientSpace(bool on_off);
    void setGraded(bool on_off);
    void setInhomogeneous(bool on_off);
    
    bool compute(const Matrix<Integer>& GivenGens,const Matrix<Integer>& GivenLinForms, const size_t nr_special_linforms);
    bool compute(const Matrix<Integer>& ComputeFrom, const Matrix<Integer>& GivenGens,const Matrix<Integer>& GivenLinForms, 
                 const size_t nr_special_linforms);
    
    Automorphism_Group();
    
}; // end class   
    
template<typename Integer>
vector<vector<long>> compute_automs(const Matrix<Integer>& Gens, const Matrix<Integer>& LinForms, const size_t nr_special_linforms, mpz_class& group_order);

vector<vector<key_t> > convert_to_orbits(const vector<long>& raw_orbits);

vector<vector<key_t> > cycle_decomposition(vector<key_t> perm, bool with_fixed_points=false);

void pretty_print_cycle_dec(const vector<vector<key_t> >& dec, ostream& out);

vector<vector<key_t> > keys(const list<boost::dynamic_bitset<> >& Partition);

list<boost::dynamic_bitset<> > partition(size_t n, const vector<vector<key_t> >& Orbits);

list<boost::dynamic_bitset<> > join_partitions(const list<boost::dynamic_bitset<> >& P1,
                                               const list<boost::dynamic_bitset<> >& P2);

vector<vector<key_t> > orbits(const vector<vector<key_t> >& Perms);

} // namespace

//---------------------------------------------------------------------------
#endif
//---------------------------------------------------------------------------
