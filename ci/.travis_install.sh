echo "ubuntu 14.04 runs cmake 2.8; we need cmake 3 or greater. installing..."
curl -sSL https://cmake.org/files/v3.5/cmake-3.5.2-Linux-x86_64.tar.gz | tar -xz
export PATH="$(pwd)"/cmake-3.5.2-Linux-x86_64/bin/:$PATH
cmake --version

#installing eigen 3
 #sudo wget "http://bitbucket.org/eigen/eigen/get/3.3.4.tar.gz" -O- | sudo tar xvz -C /usr/include/
echo "installing eigen..."
wget "http://bitbucket.org/eigen/eigen/get/3.3.4.tar.gz"
tar xzf 3.3.4.tar.gz 
mkdir eigen-3.3.4 
mv eigen-eigen*/* eigen-3.3.4

export EIGEN3_INCLUDE_DIR="$(pwd)/eigen-3.3.4/"

#_______________________________________________
  
#installing shogun library
#echo "installing shogun..." 
#sudo apt-get install -qq software-properties-common lsb-release
#sudo add-apt-repository "deb http://archive.ubuntu.com/ubuntu $(lsb_release -sc) multiverse"
#sudo add-apt-repository ppa:shogun-toolbox/nightly -y
#sudo apt-get update -y
#sudo apt-get install -qq --force-yes --no-install-recommends libshogun18
#sudo apt-get install -qq --force-yes --no-install-recommends libshogun-dev
## sudo apt-get install -qq --force-yes --no-install-recommends python-shogun
#sudo dpkg-query -l '*shogun*'
echo "installing shogun via conda..."
wget http://repo.continuum.io/miniconda/Miniconda-3.9.1-Linux-x86_64.sh \
        -O miniconda.sh
chmod +x miniconda.sh && ./miniconda.sh -b
#export PATH=/home/travis/miniconda/bin:$PATH
export PATH=/root/miniconda/bin:$PATH
conda update --yes conda
conda install --yes -c conda-forge shogun-cpp
export SHOGUN_LIB=/root/miniconda/lib/
export SHOGUN_DIR=/root/miniconda/include/

#building and installing google tests
# sudo apt-get install cmake
# sudo apt-get install libgtest-dev

#cd /usr/src/gtest; pwd
#sudo cmake CMakeLists.txt
#sudo make
#sudo cp *.a /usr/lib
#cd /home/travis/build/lacava/feat; pwd
echo "installing feat..."
cd feat; pwd
mkdir build;
cd build; pwd

cmake -DEIGEN_DIR=ON -DSHOGUN_DIR=ON ..

cd ..; pwd

make -C build VERBOSE=1
echo "running feat.."
./build/feat examples/d_enc.csv
#_________________________________________________________

