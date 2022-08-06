// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2017 The PIVX developers
// Copyright (c) 2015-2017 The ALQO developers
// Copyright (c) 2017-2018 The ojx developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"

#include "random.h"
#include "util.h"
#include "utilstrencodings.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>


using namespace std;
using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

//! Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress>& vSeedsOut, const SeedSpec6* data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7 * 24 * 60 * 60;
    for (unsigned int i = 0; i < count; i++) {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

//   What makes a good checkpoint block?
// + Is surrounded by blocks with reasonable timestamps
//   (no blocks before with a timestamp after, none after with
//    timestamp before)
// + Contains no strange transactions

static Checkpoints::MapCheckpoints mapCheckpoints =
      boost::assign::map_list_of(0, uint256("0x"));


static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
	1553809266, // * UNIX timestamp of last checkpoint block
    13,          // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the SetBestChain debug.log lines)
    2000        // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
    boost::assign::map_list_of(0, uint256("0x"));
static const Checkpoints::CCheckpointData dataTestnet = {
    &mapCheckpointsTestnet,
	1536873828,
    0,
    250};

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
    boost::assign::map_list_of(0, uint256("0x"));
static const Checkpoints::CCheckpointData dataRegtest = {
    &mapCheckpointsRegtest,
	1536873828,
    0,
    100};

class CMainParams : public CChainParams
{
public:
    CMainParams()
    {
        networkID = CBaseChainParams::MAIN;
        strNetworkID = "main";
        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0xab;
        pchMessageStart[1] = 0x22;
        pchMessageStart[2] = 0xa3;
        pchMessageStart[3] = 0xf4;
        vAlertPubKey = ParseHex("0444d74c0ea8967c7a0457f0ab8532fdd03900377780cb64a83ab8077510805a89eb9100948db395cbf5f0866b36e9697e65c35870134b52b65018a379cf02f035");                        
        nDefaultPort = 23777;
        bnProofOfWorkLimit = ~uint256(0) >> 20; // ojx starting difficulty is 1 / 2^12  //20
        nSubsidyHalvingInterval = 210000;
        nMaxReorganizationDepth = 100;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 0;
        nTargetTimespan = 1 * 60; // ojx: 2 minutes
        nTargetSpacing =  1 * 60;  // ojx: 2 minute
        nLastPOWBlock = 125000;
        nMaturity = 15;
        nMasternodeCountDrift = 20;
		nMasternodeColleteralLimxDev = 7500; //Params().MasternodeColleteralLimxDev()
        nModifierUpdateBlock = 1; // 
        nMaxMoneyOut = 720000000 * COIN;
        strDeveloperFeePayee = "NVPFLzTkuxrsreEkxNbNYM6SvJG7cv8gEQ";

        const char* pszTimestamp = "Ojx is born.";
        CMutableTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 0 * COIN;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("0486bce1bac0d543f104cbff2bd23680056a3b9ea05e1137d2ff90eeb5e08472eb500322593a2cb06fbf8297d7beb6cd30cb90f98153b5b7cce1493749e41e0284") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime = 1648773444;
        genesis.nBits = 0x1e0ffff0;
        genesis.nNonce = 23363105;
		
        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x00000132ef1cbc3fdceb752e5259f32b0326b63a721ee499ecd05c44db2bb2c0"));
        assert(genesis.hashMerkleRoot == uint256("0x545500d623963fb074720b0d34e54ebb3f0fcc7b7077838db2e30e23ac78a780"));
	
       	// New Seed Nodes added 
        vSeeds.push_back(CDNSSeedData("52.8.164.239","52.8.164.239"));  // Seed node 1		
	    vSeeds.push_back(CDNSSeedData("52.52.23.93","52.52.23.93"));  // Seed node 2
	    vSeeds.push_back(CDNSSeedData("54.241.246.39","54.241.246.39"));  // Seed node 3
	
		//public Nodes 18/07/2022
		vSeeds.push_back(CDNSSeedData("69.197.131.10","69.197.131.10"));
        vSeeds.push_back(CDNSSeedData("87.117.38.192","87.117.38.192"));
        vSeeds.push_back(CDNSSeedData("220.76.21.29","220.76.21.29"));
        vSeeds.push_back(CDNSSeedData("180.126.235.178","180.126.235.178"));
        vSeeds.push_back(CDNSSeedData("101.117.36.227","101.117.36.227"));
        vSeeds.push_back(CDNSSeedData("193.164.16.241","193.164.16.241"));
        vSeeds.push_back(CDNSSeedData("89.151.186.219","89.151.186.219"));
        vSeeds.push_back(CDNSSeedData("37.187.27.180","37.187.27.180"));
        vSeeds.push_back(CDNSSeedData("114.115.168.184","114.115.168.184"));
        vSeeds.push_back(CDNSSeedData("20.214.136.163","20.214.136.163"));
        vSeeds.push_back(CDNSSeedData("20.196.209.224","20.196.209.224"));
        vSeeds.push_back(CDNSSeedData("125.168.95.217","125.168.95.217"));
        vSeeds.push_back(CDNSSeedData("51.161.117.115","51.161.117.115"));
        vSeeds.push_back(CDNSSeedData("5.135.136.12","5.135.136.12"));
        vSeeds.push_back(CDNSSeedData("51.79.177.216","51.79.177.216"));
        vSeeds.push_back(CDNSSeedData("20.249.22.70","20.249.22.70"));
        vSeeds.push_back(CDNSSeedData("20.196.198.24","20.196.198.24"));
        vSeeds.push_back(CDNSSeedData("20.211.47.141","20.211.47.141"));
        vSeeds.push_back(CDNSSeedData("113.99.219.117","113.99.219.117"));
        vSeeds.push_back(CDNSSeedData("14.237.93.189","14.237.93.189"));
        vSeeds.push_back(CDNSSeedData("124.221.216.241","124.221.216.241"));
        vSeeds.push_back(CDNSSeedData("114.122.105.11","114.122.105.11"));
        vSeeds.push_back(CDNSSeedData("20.70.185.46","20.70.185.46"));
        vSeeds.push_back(CDNSSeedData("222.186.138.213","222.186.138.213"));
        vSeeds.push_back(CDNSSeedData("20.249.61.190","20.249.61.190"));
        vSeeds.push_back(CDNSSeedData("14.173.217.63","14.173.217.63"));
        vSeeds.push_back(CDNSSeedData("93.81.223.8","93.81.223.8"));
        vSeeds.push_back(CDNSSeedData("222.140.172.35","222.140.172.35"));
        vSeeds.push_back(CDNSSeedData("189.110.0.157","189.110.0.157"));
        vSeeds.push_back(CDNSSeedData("116.235.53.234","116.235.53.234"));
        vSeeds.push_back(CDNSSeedData("85.149.10.110","85.149.10.110"));
        vSeeds.push_back(CDNSSeedData("123.56.98.82","123.56.98.82"));
        vSeeds.push_back(CDNSSeedData("120.229.163.230","120.229.163.230"));
        vSeeds.push_back(CDNSSeedData("150.158.140.229","150.158.140.229"));
        vSeeds.push_back(CDNSSeedData("46.152.135.165","46.152.135.165"));
        vSeeds.push_back(CDNSSeedData("93.126.95.110","93.126.95.110"));
        vSeeds.push_back(CDNSSeedData("20.40.74.108","20.40.74.108"));
        vSeeds.push_back(CDNSSeedData("49.235.162.153","49.235.162.153"));
        vSeeds.push_back(CDNSSeedData("188.193.78.116","188.193.78.116"));
        vSeeds.push_back(CDNSSeedData("20.213.126.80","20.213.126.80"));
        vSeeds.push_back(CDNSSeedData("43.226.40.206","43.226.40.206"));
        vSeeds.push_back(CDNSSeedData("43.226.39.110","43.226.39.110"));
        vSeeds.push_back(CDNSSeedData("222.140.175.251","222.140.175.251"));

		
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 115);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 116);
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 83);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0xAD)(0x04)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x1E)(0x04)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();
        // 	BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md 1977 0x800007b9
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x07)(0xb9).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        fRequireRPCPassword = true;
        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fSkipProofOfWorkCheck = false;
        fTestnetToBeDeprecatedFieldRPC = false;
        fHeadersFirstSyncingActive = false;

        nPoolMaxTransactions = 3;
        strSporkKey = "04130ec0dd4e2326ae219be3b43c6ddfe08243605b853107228126237f79e24b13543a39099ef994020c39498c3f8061ac5f7c01b5be6f5ed7ffad248e326fccd6";
        strDarksendPoolDummyAddress = "NVPbvwMsazkvyyJbThNE6Edjj74JUFDdWy";
        nStartMasternodePayments = 1586225788;
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return data;
    }
};
static CMainParams mainParams;

/**
 * Testnet
 */
class CTestNetParams : public CMainParams
{
public:
    CTestNetParams()
    {
        networkID = CBaseChainParams::TESTNET;
        strNetworkID = "test";
        pchMessageStart[0] = 0x64;
        pchMessageStart[1] = 0x44;
        pchMessageStart[2] = 0x65;
        pchMessageStart[3] = 0x54;
        vAlertPubKey = ParseHex("04401424054d92fa763dade08903e2d91f0386ba9be4e1419445dc69bd62ca4a6ca7ed1827b22d6b399cc0ae800282df68bdc14a2b723d0273d58fe2d9c682ea8c");
        nDefaultPort = 23777;
        nEnforceBlockUpgradeMajority = 51;
        nRejectBlockOutdatedMajority = 75;
        nToCheckBlockUpgradeMajority = 100;
        nMinerThreads = 0;
        nTargetTimespan = 10; // ojx: 10 seconds
        nTargetSpacing = 10;  // ojx: 10 seconds
        nLastPOWBlock = 3016;
        nMaturity = 2;
        nModifierUpdateBlock = 51197; //approx Mon, 17 Apr 2017 04:00:00 GMT
        nMaxMoneyOut = 100000000 * COIN;
        strDeveloperFeePayee = "---";

        //! Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nTime = 1648773444;
        genesis.nNonce = 23363105;

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x00000132ef1cbc3fdceb752e5259f32b0326b63a721ee499ecd05c44db2bb2c0"));

        vFixedSeeds.clear();
        vSeeds.clear();
		

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 65);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 18);
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 193);
        // Testnet ojx BIP32 pubkeys start with 'DRKV'
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x3a)(0x80)(0x61)(0xa0).convert_to_container<std::vector<unsigned char> >();
        // Testnet ojx BIP32 prvkeys start with 'DRKP'
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x3a)(0x80)(0x58)(0x37).convert_to_container<std::vector<unsigned char> >();
        // Testnet ojx BIP44 coin type is '1' (All coin's testnet default)
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x01).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        fRequireRPCPassword = true;
        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;

        nPoolMaxTransactions = 2;
        strSporkKey = "0420c99cfc1bae15e20f1eb815c46712cd44ddfec00c5d6356d4e869aa89bc9ef5defc8769ef32e9d0376ddd01be9d8336a3aa16190d77ae8a7fdd0d1d6a07d68b";
        strDarksendPoolDummyAddress = "";
        nStartMasternodePayments = 1519010250;
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataTestnet;
    }
};
static CTestNetParams testNetParams;

/**
 * Regression test
 */
class CRegTestParams : public CTestNetParams
{
public:
    CRegTestParams()
    {
        networkID = CBaseChainParams::REGTEST;
        strNetworkID = "regtest";
        pchMessageStart[0] = 0x14;
        pchMessageStart[1] = 0x54;
        pchMessageStart[2] = 0x95;
        pchMessageStart[3] = 0x64;
        nDefaultPort = 31555;
        nSubsidyHalvingInterval = 150;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 1;
        nTargetTimespan = 5 * 60; // ojx: 5 minutes
        nTargetSpacing = 1 * 60;  // ojx: 1 minute
        bnProofOfWorkLimit = ~uint256(0) >> 1;
        genesis.nTime = 1648773444;
        genesis.nBits = 0x1e0ffff0;
        genesis.nNonce = 23363105;
        strDeveloperFeePayee = "---";


        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x00000132ef1cbc3fdceb752e5259f32b0326b63a721ee499ecd05c44db2bb2c0"));

        vFixedSeeds.clear(); //! Testnet mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Testnet mode doesn't have any DNS seeds.

        fRequireRPCPassword = false;
        fMiningRequiresPeers = false;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fTestnetToBeDeprecatedFieldRPC = false;
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataRegtest;
    }
};
static CRegTestParams regTestParams;

/**
 * Unit test
 */
class CUnitTestParams : public CMainParams, public CModifiableParams
{
public:
    CUnitTestParams()
    {
        networkID = CBaseChainParams::UNITTEST;
        strNetworkID = "unittest";
        nDefaultPort = 31555;
        vFixedSeeds.clear(); //! Unit test mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Unit test mode doesn't have any DNS seeds.
        strDeveloperFeePayee = "---";

        fRequireRPCPassword = false;
        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fAllowMinDifficultyBlocks = false;
        fMineBlocksOnDemand = true;
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        // UnitTest share the same checkpoints as MAIN
        return data;
    }

    //! Published setters to allow changing values in unit test cases
    virtual void setSubsidyHalvingInterval(int anSubsidyHalvingInterval) { nSubsidyHalvingInterval = anSubsidyHalvingInterval; }
    virtual void setEnforceBlockUpgradeMajority(int anEnforceBlockUpgradeMajority) { nEnforceBlockUpgradeMajority = anEnforceBlockUpgradeMajority; }
    virtual void setRejectBlockOutdatedMajority(int anRejectBlockOutdatedMajority) { nRejectBlockOutdatedMajority = anRejectBlockOutdatedMajority; }
    virtual void setToCheckBlockUpgradeMajority(int anToCheckBlockUpgradeMajority) { nToCheckBlockUpgradeMajority = anToCheckBlockUpgradeMajority; }
    virtual void setDefaultConsistencyChecks(bool afDefaultConsistencyChecks) { fDefaultConsistencyChecks = afDefaultConsistencyChecks; }
    virtual void setAllowMinDifficultyBlocks(bool afAllowMinDifficultyBlocks) { fAllowMinDifficultyBlocks = afAllowMinDifficultyBlocks; }
    virtual void setSkipProofOfWorkCheck(bool afSkipProofOfWorkCheck) { fSkipProofOfWorkCheck = afSkipProofOfWorkCheck; }
};
static CUnitTestParams unitTestParams;


static CChainParams* pCurrentParams = 0;

CModifiableParams* ModifiableParams()
{
    assert(pCurrentParams);
    assert(pCurrentParams == &unitTestParams);
    return (CModifiableParams*)&unitTestParams;
}

const CChainParams& Params()
{
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams& Params(CBaseChainParams::Network network)
{
    switch (network) {
    case CBaseChainParams::MAIN:
        return mainParams;
    case CBaseChainParams::TESTNET:
        return testNetParams;
    case CBaseChainParams::REGTEST:
        return regTestParams;
    case CBaseChainParams::UNITTEST:
        return unitTestParams;
    default:
        assert(false && "Unimplemented network");
        return mainParams;
    }
}

void SelectParams(CBaseChainParams::Network network)
{
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}

bool SelectParamsFromCommandLine()
{
    CBaseChainParams::Network network = NetworkIdFromCommandLine();
    if (network == CBaseChainParams::MAX_NETWORK_TYPES)
        return false;

    SelectParams(network);
    return true;
}
