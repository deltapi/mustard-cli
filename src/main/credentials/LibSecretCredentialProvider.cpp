#include <Provide.h>
#include "LibSecretCredentialProvider.h"
#include "CredentialProvider.h"

#ifndef WITH_LIBSECRET
ProvideDependency<CredentialProvider> credentialProvider;
#endif

#ifdef WITH_LIBSECRET

#include <glib.h>
#include <libsecret/secret.h>
#include <Depend.h>

ProvideImplementationForDependency<LibSecretCredentialProvider, CredentialProvider> keyringCredentialProvider;

const SecretSchema LibSecretCredentialProvider::secretSchema = {
    "mustard.BitbucketPassword", SECRET_SCHEMA_DONT_MATCH_NAME,
    {
        {"server", SECRET_SCHEMA_ATTRIBUTE_STRING},
        {"user", SECRET_SCHEMA_ATTRIBUTE_STRING},
        {NULL, SECRET_SCHEMA_ATTRIBUTE_STRING},
    }
};

string LibSecretCredentialProvider::getPasswordFor ( const string &serverName, const string &userName )
{
    GError *gError = nullptr;
    gchar *password = secret_password_lookup_sync (
                          &secretSchema,
                          nullptr,
                          &gError,
                          "user",
                          userName.c_str(),
                          "server",
                          serverName.c_str(),
                          NULL
                      );
    if ( !password ) {
        return {"", ""};
    }
    if ( gError ) {
        throw MustardException ( gError->message );
    }
    string passwordCopy ( password );
    secret_password_free ( password );
    return passwordCopy;
}

bool LibSecretCredentialProvider::saveCredentials ( const string &serverName, const Credentials &credentials )
{
    GError *gError = nullptr;
    secret_password_store_sync (
        &secretSchema,
        SECRET_COLLECTION_DEFAULT,
        "BitbucketServerPassword",
        credentials.password.c_str(),
        nullptr,
        &gError,
        "user",
        credentials.username.c_str(),
        "server",
        serverName.c_str(),
        nullptr
    );
    if ( gError ) {
        printf ( "Had problems storing password: %s\n", gError->message );
        return false;
    }
    return true;
}

bool LibSecretCredentialProvider::isReady()
{
    return true;
}

LibSecretCredentialProvider::~LibSecretCredentialProvider() = default;

#endif
