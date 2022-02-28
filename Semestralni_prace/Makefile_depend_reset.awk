BEGIN{
    endFound = 0;
}
{
    if (endFound == 0)
        print $0;
    if ($0 == "# DELETE_THESE_UNDER_ME_ON_DEPEND")
        endFound = 1;
}
