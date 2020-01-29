/* Initialize `key` with a public key */
if(1 != EVP_DigestVerifyInit(mdctx, NULL, EVP_sha256(), NULL, key)) goto err;

/* Initialize `key` with a public key */
if(1 != EVP_DigestVerifyUpdate(mdctx, msg, strlen(msg))) goto err;

if(1 == EVP_DigestVerifyFinal(mdctx, sig, slen))
{
    /* Success */
}
else
{
    /* Failure */
}