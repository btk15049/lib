//! @cond
#define BOOST_TEST_MAIN
//! @endcond
#include "structure/SegmentManager.hpp"
#include <boost/test/included/unit_test.hpp>
#include <vector>


BOOST_AUTO_TEST_SUITE(SegmentManagerClass)

void validate(std::vector<Segment>& naive, SegmentManager& target) {
    auto isInAllSegments = [](int p, const std::vector<Segment>& sgs) {
        for (auto segment : sgs) {
            if (in(p, segment)) {
                return true;
            }
        }
        return false;
    };
    for (int p = -100; p <= 100; p++) {
        bool isInNaive  = isInAllSegments(p, naive);
        bool isInTarget = isInAllSegments(p, target.all());
        BOOST_CHECK_EQUAL(isInNaive, isInTarget);
    }
}

void addSegment(std::vector<Segment>& naive, SegmentManager& target, int l,
                int r) {
    naive.push_back(Segment(l, r));
    target.add(Segment(l, r));
    validate(naive, target);
}

void deleteSegment(std::vector<Segment>& naive, SegmentManager& target, int l,
                   int r) {
    std::vector<Segment> next;
    for (auto& it : naive) {
        if (in(Segment(l, r), it)) {
            next.push_back(Segment(it.l, l));
            next.push_back(Segment(r, it.r));
        }
        else if (overlap(Segment(l, r), it)) {
            // remove
        }
        else if (in(l, it)) {
            next.push_back(Segment(it.l, l));
        }
        else if (in(r - 1, it)) {
            next.push_back(Segment(r, it.r));
        }
        else {
            next.push_back(it);
        }
    }
    swap(naive, next);
    target.erase(Segment(l, r));
    validate(naive, target);
}


BOOST_AUTO_TEST_CASE(Construct) {
    SegmentManager sgs;
    BOOST_CHECK_EQUAL((int)sgs.all().size(), 0);
}

BOOST_AUTO_TEST_CASE(AddAndErase) {
    SegmentManager target;
    std::vector<Segment> naive;

    addSegment(naive, target, -5, 5);
    addSegment(naive, target, 1, 2);
    deleteSegment(naive, target, 0, 100);
}

BOOST_AUTO_TEST_SUITE_END()