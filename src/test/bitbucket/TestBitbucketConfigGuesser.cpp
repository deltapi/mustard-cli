#include <gtest/gtest.h>
#include "../comments/GitClientForTest.h"
#include "../../main/bitbucket/BitBucketConfigGuesser.h"

using namespace testing;

class TestBitbucketConfigGuesser : public Test
{
public:
    TestBitbucketConfigGuesser() :
        guesser ( &gitClient ) {}
    GitClientForTest gitClient;
    BitBucketConfigGuesser guesser;
    const char *const https_url = "https://imgrundm@bitbucket.int.tngtech.com/scm/~imgrundm/poormansdi.git";
    const char *const ssh_url = "ssh://git@bitbucket.int.tngtech.com:122/~imgrundm/poormansdi.git";
};

TEST_F ( TestBitbucketConfigGuesser, Unit_Http_ServerName )
{
    EXPECT_CALL ( gitClient, getConfigValue ( StrEq ( "remote.origin.url" ) ) ).WillOnce (
        Return ( https_url ) );

    guesser.guess();
    EXPECT_STREQ ( "bitbucket.int.tngtech.com", guesser.getServer().c_str() );
}

TEST_F ( TestBitbucketConfigGuesser, Unit_Http_ProjectKey )
{
    EXPECT_CALL ( gitClient, getConfigValue ( StrEq ( "remote.origin.url" ) ) ).WillOnce (
        Return ( https_url ) );

    guesser.guess();
    EXPECT_STREQ ( "poormansdi", guesser.getProjectKey().c_str() );
}

TEST_F ( TestBitbucketConfigGuesser, Unit_Http_RepositorySlug )
{
    EXPECT_CALL ( gitClient, getConfigValue ( StrEq ( "remote.origin.url" ) ) ).WillOnce (
        Return ( https_url ) );

    guesser.guess();
    EXPECT_STREQ ( "~imgrundm", guesser.getRepositorySlug().c_str() );
}

TEST_F ( TestBitbucketConfigGuesser, Unit_Ssh_ServerName )
{
    EXPECT_CALL ( gitClient, getConfigValue ( StrEq ( "remote.origin.url" ) ) ).WillOnce (
        Return ( ssh_url ) );

    guesser.guess();
    EXPECT_STREQ ( "bitbucket.int.tngtech.com", guesser.getServer().c_str() );
}

TEST_F ( TestBitbucketConfigGuesser, Unit_Ssh_ProjectKey )
{
    EXPECT_CALL ( gitClient, getConfigValue ( StrEq ( "remote.origin.url" ) ) ).WillOnce (
        Return ( ssh_url ) );

    guesser.guess();
    EXPECT_STREQ ( "poormansdi", guesser.getProjectKey().c_str() );
}

TEST_F ( TestBitbucketConfigGuesser, Unit_Ssh_RepositorySlug )
{
    EXPECT_CALL ( gitClient, getConfigValue ( StrEq ( "remote.origin.url" ) ) ).WillOnce (
        Return ( ssh_url ) );

    guesser.guess();
    EXPECT_STREQ ( "~imgrundm", guesser.getRepositorySlug().c_str() );
}
