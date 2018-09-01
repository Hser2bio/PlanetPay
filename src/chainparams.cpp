// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "assert.h"

#include "chainparams.h"
#include "main.h"
#include "util.h"

#include <boost/assign/list_of.hpp>

using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

//
// Main network
//

// Convert the pnSeeds array into usable address objects.
static void convertSeeds(std::vector<CAddress> &vSeedsOut, const unsigned int *data, unsigned int count, int port)
{
     // It'll only connect to one or two seed nodes because once it connects,
     // it'll get a pile of addresses with newer timestamps.
     // Seed nodes are given a random 'last seen time' of between one and two
     // weeks ago.
     const int64_t nOneWeek = 7*24*60*60;
    for (unsigned int k = 0; k < count; ++k)
    {
        struct in_addr ip;
        unsigned int i = data[k], t;
        
        // -- convert to big endian
        t =   (i & 0x000000ff) << 24u
            | (i & 0x0000ff00) << 8u
            | (i & 0x00ff0000) >> 8u
            | (i & 0xff000000) >> 24u;
        
        memcpy(&ip, &t, sizeof(ip));
        
        CAddress addr(CService(ip, port));
        addr.nTime = GetTime()-GetRand(nOneWeek)-nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

class CMainParams : public CChainParams {
public:
    CMainParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0x2c;
        pchMessageStart[1] = 0x3e;
        pchMessageStart[2] = 0xc1;
        pchMessageStart[3] = 0xb3;
        vAlertPubKey = ParseHex("042bfc856fbaa86ff8dccb266cf5b52b7a91acda94feae02541688a03f6efcfffcaf2bfe573d0349059a2178f43b3cea7b90950508d5c7e8df11f4feef2c008323");
        nDefaultPort = 13127;
        nRPCPort = 13126;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 16);

        // Build the genesis block. Note that the output of the genesis coinbase cannot
        // be spent as it did not originally exist in the database.
        //
		//CBlock(hash = 0000153d1dea38532ed6798bc1bb0092b41d0b487faeafcace26ab8375e93475, ver = 1, hashPrevBlock = 0000000000000000000000000000000000000000000000000000000000000000, hashMerkleRoot = 5f00f8f40b1fa90147e87663bdc021a8d39ac639a557b794eac52aa26ddefda8, nTime = 1513740600, nBits = 1f00ffff, nNonce = 141350, vtx = 1, vchBlockSig = )
		//	Coinbase(hash = 5f00f8f40b1fa90147e87663bdc021a8d39ac639a557b794eac52aa26ddefda8, nTime = 1513740600, ver = 1, vin.size = 1, vout.size = 1, nLockTime = 0)
		//	CTxIn(COutPoint(0000000000, 4294967295), coinbase 00012a26323020446563203230313720426974636f696e204c696768746e696e672052656c656173652e)
		//	CTxOut(empty)
		//
		//	vMerkleTree:  5f00f8f40b1fa90147e87663bdc021a8d39ac639a557b794eac52aa26ddefda8

        const char* pszTimestamp = "2018 Planetpay coin";
        std::vector<CTxIn> vin;
        vin.resize(1);
        vin[0].scriptSig = CScript() << 0 << CBigNum(42) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        std::vector<CTxOut> vout;
        vout.resize(1);
        vout[0].SetEmpty();
        CTransaction txNew(1, 1513740600, vin, vout, 0);
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime    = 1535351991;
        genesis.nBits    = 520159231; 
        genesis.nNonce   = 141350; 		

        hashGenesisBlock = genesis.GetHash();
        
        assert(hashGenesisBlock == uint256("0x2050fb16ababb9defa5be772b9689db0882dec59af7caafccc52f712df5c4e29"));
        assert(genesis.hashMerkleRoot == uint256("0xf0f9c1b7b9de62212f03c62100d891ed56c302a6e6886201d24c53d467d63a26"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,55);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,16);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,63);
        base58Prefixes[STEALTH_ADDRESS] = std::vector<unsigned char>(1,75);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x05)(0x27)(0xB1)(0x1E).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x05)(0x27)(0xAE)(0xE4).convert_to_container<std::vector<unsigned char> >();

        vSeeds.push_back(CDNSSeedData("n0", "173.249.1.107"));
        vSeeds.push_back(CDNSSeedData("n1", "188.166.5.35"));
		vSeeds.push_back(CDNSSeedData("n2", "178.128.174.60"));
		vSeeds.push_back(CDNSSeedData("n3", "46.101.121.162"));
		vSeeds.push_back(CDNSSeedData("n3", "142.93.30.47"));
        convertSeeds(vFixedSeeds, pnSeed, ARRAYLEN(pnSeed), nDefaultPort);

        nPoolMaxTransactions = 3;
        //strSporkKey = "046f78dcf911fbd61910136f7f0f8d90578f68d0b3ac973b5040fb7afb501b5939f39b108b0569dca71488f5bbf498d92e4d1194f6f941307ffd95f75e76869f0e";
        //strMasternodePaymentsPubKey = "046f78dcf911fbd61910136f7f0f8d90578f68d0b3ac973b5040fb7afb501b5939f39b108b0569dca71488f5bbf498d92e4d1194f6f941307ffd95f75e76869f0e";
        strDarksendPoolDummyAddress = "PPwhFPkacF2HqKZBtaBiuE9TizdtBBjCD6";
        nLastPOWBlock = 1000;
        nPOSStartBlock = 51;
    }

    virtual const CBlock& GenesisBlock() const { return genesis; }
    virtual Network NetworkID() const { return CChainParams::MAIN; }

    virtual const vector<CAddress>& FixedSeeds() const {
        return vFixedSeeds;
    }
protected:
    CBlock genesis;
    vector<CAddress> vFixedSeeds;
};
static CMainParams mainParams;


//
// Testnet
//

class CTestNetParams : public CMainParams {
public:
    CTestNetParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0xc1;
        pchMessageStart[1] = 0xb2;
        pchMessageStart[2] = 0xa4;
        pchMessageStart[3] = 0xb7;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 16);
        vAlertPubKey = ParseHex("04a983220ea7a38a7106385003fef77896538a382addcc389cc66f3c98751d9af423a097666767676259351a98a8aaa628a1fd644c3232678c5845384c744ff8d7");
        nDefaultPort = 20114;
        nRPCPort = 20115;
        strDataDir = "testnet";

        // Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nBits  = 520159231; 
        genesis.nNonce = 141350;
      
        assert(hashGenesisBlock == uint256("0x2050fb16ababb9defa5be772b9689db0882dec59af7caafccc52f712df5c4e29"));

        vFixedSeeds.clear();
        vSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,127);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,196);
        base58Prefixes[SECRET_KEY]     = std::vector<unsigned char>(1,239);
        base58Prefixes[STEALTH_ADDRESS] = std::vector<unsigned char>(1,40);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x35)(0x87)(0xCF).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x35)(0x83)(0x94).convert_to_container<std::vector<unsigned char> >();

        convertSeeds(vFixedSeeds, pnTestnetSeed, ARRAYLEN(pnTestnetSeed), nDefaultPort);

        nLastPOWBlock = 0x7fffffff;
    }
    virtual Network NetworkID() const { return CChainParams::TESTNET; }
};
static CTestNetParams testNetParams;


static CChainParams *pCurrentParams = &mainParams;

const CChainParams &Params() {
    return *pCurrentParams;
}

void SelectParams(CChainParams::Network network) {
    switch (network) {
        case CChainParams::MAIN:
            pCurrentParams = &mainParams;
            break;
        case CChainParams::TESTNET:
            pCurrentParams = &testNetParams;
            break;
        default:
            assert(false && "Unimplemented network");
            return;
    }
}

bool SelectParamsFromCommandLine() {
    
    bool fTestNet = GetBoolArg("-testnet", false);
    
    if (fTestNet) {
        SelectParams(CChainParams::TESTNET);
    } else {
        SelectParams(CChainParams::MAIN);
    }
    return true;
}
