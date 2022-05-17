BEGIN{
    endFound = 0;
}
{
    if ($0 == "# PRIVATE")
        endFound = 1;
    if (endFound == 0)
        print $0;
}
